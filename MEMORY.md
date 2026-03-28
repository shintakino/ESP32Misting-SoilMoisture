## Long-term memory for Shintakino Alex
Last updated: 2026-03-28

## Active Projects
<!-- Update this as projects start, pause, or ship -->
* Building an AI agent platform with OpenClaw
* Designing network infra for a new product launch

## Tech Stack & Tools
### Languages
* Python, TypeScript, Rust, Go, SQL, Shell Scripting
### Frameworks & Libraries
* FastAPI, Next.js, [LangChain](https://python.langchain.com/)
### Infrastructure & DevOps
* Docker, Kubernetes, Cloudflare, Nginx
### AI & ML Tools
* OpenClaw, Ollama, Anthropic API, HuggingFace
### Security Stack (NEW — Required)
* **Secrets management:** HashiCorp Vault (via env isolation)
* **Auth strategy:** JWT, OAuth, session-based
* **Network security:** Zero Trust principles, firewall rules, VPC isolation
* **Dependency scanning:** Snyk, Trivy
* **Logging & monitoring:** SIEM, Loki, ELK stack
* **Pen-testing tools:** Burp Suite, Wireshark
### Design Tools
* Figma
### Preferred Editor / IDE
* VS Code, Neovim

## Goals & Priorities
### Short-term (Next 30 days)
* Implement baseline security architecture.
* Ship initial version of AI agent platform.
### Medium-term (Next 90 days)
* Achieve production-grade security posture for core systems.
* Integrate advanced AI research into agent capabilities.
### Long-term (6–12 months)
* Establish scalable and resilient AI agent infrastructure.
* Maintain a proactive threat intelligence and response capability.

## Personal Preferences & Habits
### Work Style
* Operates across multiple disciplines simultaneously
* Timezone: Asia/Manila (PHT, UTC+8)
* Prefers strategic, high-level communication
* Moves fast — doesn't need things explained twice
* Builds with security and resilience in mind by default

### Response Preferences
* Lead with the answer or recommendation
* Structure output only when it aids clarity
* Flag issues proactively, especially security risks
* Peer-level tone always

## Things to Never Do
* Don't use filler phrases ("Great question!", "Certainly!")
* Don't over-explain basics
* Don't offer a menu of options without a clear recommendation
* Don't shorten my name or use nicknames
* Don’t ignore obvious security risks for speed

## Security Posture (NEW — Operational Layer)
### Default Mindset
* Assume systems are exposed and adversarial traffic exists
* Trust nothing by default (zero trust mindset)
* Every feature has an implicit threat model

### Non-Negotiables
* No plaintext secrets in code, logs, or configs
* All critical endpoints require authentication
* Validate and sanitize all external inputs
* Encrypt sensitive data in transit and at rest
* Principle of least privilege everywhere

### Risk Awareness
* Always consider: Data exposure, unauthorized access, dependency vulnerabilities, misconfigured infrastructure.

### Incident Readiness
* Logs must support debugging AND forensics
* Failures should be observable, not silent
* Systems should degrade safely, not catastrophically
