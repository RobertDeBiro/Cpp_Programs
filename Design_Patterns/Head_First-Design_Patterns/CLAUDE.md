# Project Guidelines - Head First Design Patterns (C++20)

## UML Diagram Standards

### File Naming
- Name UML files after the pattern: `Strategy_Pattern.puml`, `Observer_Pattern.puml`, etc.
- Do NOT use generic names like `diagram.puml`

### Content Style
- **NO comments** in PlantUML files (no `'` comment lines)
- **NO notes** (no `note` blocks)
- Only include: classes, interfaces, and relationships
- Keep diagrams clean and professional

### Styling
- Use consistent PlantUML styling attributes:
  - Color definitions at top (!define)
  - skinparam settings for professional look
  - Rounded corners (RoundCorner 5)
  - No shadows (shadowing false)
  - Consistent border thickness and colors
  - Interface background: #E1F5FE
  - Abstract class background: #FFE0B2
  - Concrete class background: #FFF9C4

## Implementation Standards

### Code Structure
- **Header-only implementations**: All code in `.h` files in `inc/` directory
- `src/` directory remains empty (except for `main.cpp` in project root)
- Modern C++20 features: smart pointers, RAII, virtual destructors, const correctness
- SonarQube compliant: strict compiler warnings (-Wall -Wextra -Wpedantic -Werror)

### Documentation
- README.md: Pattern overview, usage, building instructions
- Pattern-specific .md file (e.g., `State.md`, `Template_Method.md`): Detailed architectural analysis
- NO temporary status files (like PROJECT_SUMMARY.txt)

### Build System
- CMakeLists.txt with C++20 standard
- Build scripts in `scripts/`: conf.sh, build.sh, run.sh, all.sh
- Long separator format in all.sh (user-customized)

## Design Pattern Requirements

### Analysis Focus
- **PRIMARY GOAL**: Understand PRINCIPLES and ARCHITECTURAL THINKING, not just patterns
- Show BAD architecture examples (pain points before pattern)
- Real-world examples (rotate: Network → Robotics → Embedded)
- Architectural thinking process

### Real-World Example Rotation
1. Strategy → Robotics
2. Observer → Network
3. Decorator → Embedded
4. Factory Method → Network
5. Command → Robotics
6. Adapter → Embedded
7. Facade → Network
8. Template Method → Robotics
9. Iterator & Composite → Embedded
10. State → Network
