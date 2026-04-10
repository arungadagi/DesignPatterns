# Requirements Review Report — REQ-101..REQ-105 verification

Verdict: failure

Rationale (short): The generator output (REQ-101..REQ-105) provides clear, testable acceptance criteria and follow-up tickets that largely close the five previously-identified gaps (product KPIs, AI-review SLA/runbook, DR/backups, secrets rotation, API rate-limits). However, a small set of implementation-critical clarifications remain (notably concrete short-term rate-limit numbers and a few ops/security runbook details), so I cannot mark all blocking gaps as closed.

Mapping & evidence (one-line citations):
- Product KPIs — Addressed (ACs + alerts): REQ-101 AC-101.1: "emit events with fields {job_id, user_tier, ticker, modules, duration_ms, outcome, ai_cost_estimate} ... retain metrics for 90 days." (file: `.github/hooks/logs/requirements-generator-output.md`, excerpt)
	- Cross-reference: SRS FR-19: "Example thresholds: AI job failure rate >1% over 1 hour → pager... Monitoring runbooks and alert definitions are stored under `/specs/ops/`." (file: `SRS.md`, excerpt)
- AI-review SLA & Runbook — Addressed (validation + triage SLAs): REQ-102 AC-102.2: "ops must triage within 2 hours during ops window (08:00–20:00 IST) and within 8 hours outside ops hours..." (file: `.github/hooks/logs/requirements-generator-output.md`)
	- Cross-reference: SRS FR-16: "Default tolerances: PAT ±1.0%, Revenue ±2.0%... failing validation sets `validation_status` to `flagged` and writes a record to `admin_review_queue`." (file: `SRS.md`)
- DR / Backups — Addressed (RPO/RTO + tests): REQ-103 AC-103.1: "hourly incremental backups + daily full snapshots... RPO ≤ 1 hour; RTO ≤ 2 hours for core services (analysis ingestion, DB)." (file: `.github/hooks/logs/requirements-generator-output.md`)
	- Cross-reference: SRS FR-18: "Use AES-256 for data at rest, KMS for key management..." (file: `SRS.md`)
- Secrets Rotation — Addressed (KMS + automation + CI guards): REQ-104 AC-104.1: "rotation window arrives (default 90 days) ... automated rotation job updates secrets... and records rotation event in audit logs." (file: `.github/hooks/logs/requirements-generator-output.md`)
	- Cross-reference: SRS FR-18: "KMS for key management, key-rotation policy." (file: `SRS.md`)
- API Rate-Limits & Quotas — Partially addressed: REQ-105 includes behavior for short-term/long-term quota breaches and provider 429 handling, and sets concurrency >2 as a policy (REQ-105.3). (file: `.github/hooks/logs/requirements-generator-output.md`)
	- Cross-reference: SRS FR-17: "Free-tier quota (`3 free analyses / month`) resets on calendar-month boundaries (UTC 00:00 on the 1st)." (file: `SRS.md`)

Remaining gaps / clarifications required (concise):
1) API short-term numeric thresholds — REQ-105 references "burst/minute" behaviour but does not specify numeric per-tier values (e.g., N req/min for Free/Pro/Teams). This blocks gateway/config implementation and load-testing.
2) Metrics backend, naming & retention alignment — REQ-101 prescribes fields and 90-day metrics retention, but SRS retains audit logs for 1 year; decide canonical retention and metric backend (Prometheus/Grafana, metrics naming/tagging, sampling rate).
3) Runbook ownership & escalation matrix — REQ-102 defines triage SLAs and automated actions but lacks the on-call roster/roles, escalation contacts, and the exact triage UI/hand-off procedure.
4) Emergency secret/key-rotation (break‑glass) — REQ-104 gives scheduled rotation (90 days) and CI guards but does not define emergency rotation workflow for compromised keys (who initiates, how to roll keys for backups/KMS without service outage).

Next steps (1–3 bullets):
- Finalize and record numeric short-term rate limits per tier and provider backoff params (max retries, base/backoff, jitter, retry cap) and update REQ-105 + `/specs/api/rate_limits.md` (priority: blocker).
- Align retention policies: confirm metrics retention vs audit log retention vs backup retention and choose metric backend & naming conventions; update REQ-101 and SRS FR-18/FR-19 accordingly.
- Add runbook owners/escalation contacts and an emergency secrets rotation play to `/specs/ops/ai_review_runbook.md` and `/specs/ops/dr_playbook.md`; then assign the follow-up tickets (TICKET 1–5) to SRE/security/product owners for implementation.

Summary: REQ-101..REQ-105 materially close the original review gaps and are well-formed, testable requirements. A small set of implementation-critical values and ops/security runbook details still needs to be added before closing the review as `success`.

-- requirements-review agent

Todo (updated):
- [x] Read input files: `.github/hooks/logs/requirements-generator-output.md`, `prd.md`, `SRS.md`, `requirement.md` — completed.
- [x] Analyze review output & draft REQs (REQ-101..REQ-105) — completed.
- [x] Produce follow-up ticket skeletons (TICKET 1–5) — completed.
- [x] Persist this review to `.github/hooks/logs/requirements-review-output.md` — completed.
- [ ] SKIPPED: Persist REQ-101..REQ-105 into `SRS.md` and create `/specs/ops/*` files — SKIPPED (requires PR / owner approval; can implement on request).

