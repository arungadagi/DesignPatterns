# Security & Compliance Appendix

This document records actionable security controls required by FR-18.

Encryption & Keys
- Data at rest: AES-256 (GCM preferred) for application-level sensitive data.
- Database: enable encryption at rest via cloud provider; use column encryption (PGP/AES) for highly sensitive fields.
- Key management: use cloud KMS (AWS KMS / GCP KMS / Azure Key Vault) or Supabase KMS for key rotation and access controls.

In-transit
- Enforce TLS 1.2+ for all endpoints. Reject older protocols and weak ciphers.

Payment data
- Do NOT store raw payment instrument data. Use Razorpay tokens and webhooks. Limit PCI scope by delegating card entry to Razorpay-hosted flows.

Access control
- Implement RBAC: roles include `admin`, `ops`, `engineer`, `qa`, `user`.
- Admin actions (prompt template edits, review queue triage) must be logged and require `admin` role.

Logging & Audit
- Retain audit logs for at least 1 year (per FR-18). Logs should include user_id, action, resource, timestamp.
- Protect logs with restricted access; use WORM storage if required for compliance.

Secrets
- Store secrets in KMS-backed secret store (.env should be only for local dev); rotate secrets every 90 days.

Acceptance Tests (examples)
- Verify that the DB column for `raw_ai_output` and `user_profiles.ssn` (if present) are encrypted.
- Verify that webhook endpoints require a valid signature and reject invalid signatures (returns 400).
