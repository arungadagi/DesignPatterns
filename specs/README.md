Specs and validation
====================

This folder contains machine-readable artifacts used by engineering and CI to validate AI outputs and external integrations.

Locations
- `/specs/schemas/` — JSON Schema (Draft-07) files for each AI module (used by the validation pipeline and CI).
- `/specs/api/` — OpenAPI snippets for external integrations (webhooks, sync endpoints).
- `/specs/security.md` — (placeholder) security appendix and PCI notes.

Validation
- Use `ajv` (Node) or `jsonschema` (Python) to validate AI outputs against the JSON Schemas.

Example (AJV CLI):

```bash
npx ajv validate -s specs/schemas/business_analysis.schema.json -d samples/ai/business_analysis.json
```

Default tolerances (used by AI reconciliation pipeline):
- PAT: ±1.0%
- Revenue: ±2.0%
- Other aggregates: ±2.0%

Add more schemas and API specs as the product grows.
