#!/usr/bin/env bash
# Helper script for the requirements-review -> requirements-generator hook.
# This script is a lightweight helper intended for CI or local automation where the
# agent runtime can execute hooks. It prepares inputs for the `requirements-generator`
# agent and writes log/marker files so automation systems can pick up the event.

set -euo pipefail

LOG_DIR=".github/hooks/logs"
mkdir -p "$LOG_DIR"

TIMESTAMP="$(date --iso-8601=seconds)"
echo "$TIMESTAMP - requirements-generator hook triggered by requirements-review" >> "$LOG_DIR/trigger.log"

REVIEW_OUTPUT="$LOG_DIR/requirements-review-output.md"
GEN_INPUT="$LOG_DIR/requirements-generator-input.md"

if [ -f "$REVIEW_OUTPUT" ]; then
  cp "$REVIEW_OUTPUT" "$GEN_INPUT"
  echo "$TIMESTAMP - copied review output to generator input" >> "$LOG_DIR/trigger.log"
else
  echo "$TIMESTAMP - warning: review output not present; creating placeholder input" >> "$LOG_DIR/trigger.log"
  echo "# Placeholder input for requirements-generator\nNo review output found; generator should run in discovery mode." > "$GEN_INPUT"
fi

# Marker file for automation systems or CI to pick up
touch .github/hooks/generator_triggered.marker

echo "requirements-generator hook: logged trigger, prepared input, and created marker file."

exit 0
