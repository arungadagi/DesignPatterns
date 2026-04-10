#!/usr/bin/env bash
# Helper script for the requirements-review hook.
# This script is a placeholder showing how the hook can request a review run.
# It writes a log entry and a marker file; integrate with your agent runtime to invoke the
# `requirements-review` agent programmatically if available.

set -euo pipefail

LOG_DIR=".github/hooks/logs"
mkdir -p "$LOG_DIR"

echo "$(date --iso-8601=seconds) - requirements-review hook triggered by requirements-generator" >> "$LOG_DIR/trigger.log"

# Marker file for automation systems or CI to pick up
touch .github/hooks/review_requested.marker

echo "requirements-review hook: logged trigger and created marker file."

exit 0
