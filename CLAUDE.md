---
name: claude-instructions
description: "Workspace instructions for Claude-style agents: guidance for natural-language assistants, expectations for edits, and example prompts."
applyTo:
  - "**/*.cpp"
  - "**/*.md"
---

# Workspace Instructions — Claude (Anthropic)

Purpose: Give a Claude-style assistant the same repository context and clear guardrails for edits, while encouraging natural-language explanations and stepwise reasoning.

**Quick context**
- This repo contains C++ design pattern examples. Key docs and examples:
  - [creational/factory/FactoryPattern.md](creational/factory/FactoryPattern.md#L1-L200)
  - [creational/factory/example/FactoryExample.cpp](creational/factory/example/FactoryExample.cpp#L1-L200)

**Build & verify**
- To compile the Factory example, run:

```bash
g++ -g -std=c++17 creational/factory/example/FactoryExample.cpp -o FactoryExample
./FactoryExample
```

On Windows with Cygwin/MSYS/MinGW, adapt the compiler path as needed (for example, `C:\cygwin64\bin\g++.exe`).

**Agent expectations (Claude)**
- Use stepwise, explanatory language: outline plan, then produce the change as a small patch.
- Always ask clarifying questions for ambiguous requests.
- When editing code, prefer small, testable patches and include verification steps (build + run commands).
- Highlight any risk or breaking-change potential before applying edits.

**Example prompts for Claude**
- "Explain how the Factory Method example works and suggest a small improvement to Creator::someOperation()."
- "Create a short checklist (3 steps) to validate the Factory example after a code change."

**Next steps / Extensions**
- Consider adding an `AGENTS.md` index that links to both this file and `.github/copilot-instructions.md` if you want a single discovery point for multiple agents.
