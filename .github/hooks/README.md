# Hooks: requirements-review -> requirements-generator

This folder contains a small, non-blocking hook that triggers the `requirements-generator`
agent when the `requirements-review` agent finishes successfully.

Files added
- `requirements-review-to-generator.hook.json` — hook configuration (event, condition, action).
- `run_requirements_generator.sh` — helper script to prepare inputs and write a marker/log so CI or automation can pick up the event.

How it works
1. The agent runtime should emit an `AgentRunCompleted` event with `trigger_agent: requirements-review` when a run finishes.
2. If the hook condition (status == "success") matches, the runtime invokes the action: call `requirements-generator` with the indicated inputs.
3. The helper script can be used in CI or locally to prepare inputs for the generator and create a marker file.

Quick test (local / CI)
1. Create a fake review output to simulate the reviewer:

```bash
mkdir -p .github/hooks/logs
echo "# Sample review output\nFound gaps: auth flow missing" > .github/hooks/logs/requirements-review-output.md
```

2. Run the helper script that prepares generator input and creates a marker file:

```bash
./.github/hooks/run_requirements_generator.sh
```

3. Verify the hook ran by inspecting:

 - `.github/hooks/logs/trigger.log`
 - `.github/hooks/logs/requirements-generator-input.md`
 - the presence of `.github/hooks/generator_triggered.marker`

Ambiguities & questions for you
- Does your agent runtime support the `AgentRunCompleted` event and the `invoke_agent` action shape used in the JSON? If not, which event/action schema should I target?
- Should the hook be blocking (prevent further progress until the generator finishes) or non-blocking? It is currently non-blocking.
- Would you like the hook to automatically create issues (e.g., GitHub Issues) for follow-up items? The JSON includes a `create_follow_up_tickets` param but no implementation.

Next steps I can take
- Wire in a simple implementation that posts follow-up GitHub issues when `create_follow_up_tickets` is enabled (requires GitHub token and user approval).
- Update the hook to be blocking if you prefer enforcement at runtime.
