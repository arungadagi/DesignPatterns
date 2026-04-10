---
name: copilot-instructions
description: "Workspace instructions for GitHub Copilot / Copilot Chat: build, tests, conventions, and agent behavior. Prefer targeted, minimal patches and asking clarifying questions."
applyTo:
  - "**/*.cpp"
  - "**/*.h"
  - "**/*.md"
---

# Workspace Instructions — GitHub Copilot

Purpose: Help contributors and AI assistants (Copilot Chat) quickly understand repository layout, build/test commands, coding conventions, and how the agent should behave when making edits.

**Repo summary**
- This repository demonstrates classic design patterns implemented in C++ (see the `creational/`, `behaviaral/` folders).
- Canonical example for the Factory Method: [creational/factory/example/FactoryExample.cpp](creational/factory/example/FactoryExample.cpp#L1-L200)
- Pattern documentation: [creational/factory/FactoryPattern.md](creational/factory/FactoryPattern.md#L1-L200)

**Build & run (local)**
- Use a C++17-capable compiler. Examples below assume `g++` is on PATH or available via Cygwin/MinGW.

Powershell (Windows):

```powershell
cd creational/factory/example
C:\cygwin64\bin\g++.exe -g -std=c++17 FactoryExample.cpp -o FactoryExample.exe
.\FactoryExample.exe
```

POSIX (Linux/macOS):

```bash
cd creational/factory/example
g++ -g -std=c++17 FactoryExample.cpp -o FactoryExample
./FactoryExample
```

**Conventions & preferences**
- Follow simple, idiomatic C++: prefer RAII and smart pointers (`std::unique_ptr`), use `-std=c++17`.
- Keep changes minimal: prefer small, reviewable patches and incremental commits.
- The repository owner prefers strict TDD: derive tests from requirements first, then implement code to satisfy tests.

**Agent behavior (how Copilot should act)**
- Ask clarifying questions before making non-trivial edits.
- Prefer editing via small diffs using the repository editing tools (apply_patch). Do not produce big unreviewed replacements.
- When proposing fixes, include a short rationale, a concise patch, and unit/usage instructions to verify the change (build + run steps).
- Do not run external network calls or modify system configuration files without explicit permission.
- If uncertain about project conventions, reference this file and the pattern docs rather than guessing.

**What to include in suggested patches**
- One-line summary of the change.
- The minimal code diff (apply_patch-style). Avoid reformatting unrelated files.
- A short test or command to run to verify the fix.

**Example prompts for Copilot Chat**
- "Find and fix the build/link error in creational/factory/example/FactoryExample.cpp — propose a minimal patch and build steps."
- "Add a unit-test skeleton for the Factory Method example and explain the test strategy (TDD-first)."
- "Refactor Creator::someOperation() to avoid using raw pointers; provide the patch and verification steps."

**Link, don't embed**
- Prefer linking to canonical docs or files in this repo rather than duplicating large sections. See [creational/factory/FactoryPattern.md](creational/factory/FactoryPattern.md#L1-L200).

If you need a different scope (user-only instructions, or targeted applyTo paths), place instructions under the user prompts folder or create file-level instructions using `applyTo` globs.
