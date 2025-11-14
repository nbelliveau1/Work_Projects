# Pokémon Battle Q-Learning Agent

This repository implements a minimal end-to-end reinforcement learning (RL) agent that learns to win 1-v-1 Pokémon battles via Q-learning. It is designed as a compact, readable example of applying core RL concepts (state representation, action selection, and value updates) to a familiar, turn-based game environment.

The project is intentionally lightweight—everything is contained in a single Python file—so reviewers can quickly understand the design, reasoning, and implementation decisions. This codebase is referenced on my résumé as an example of my ability to:

- Model decision-making problems as Markov Decision Processes (MDPs)
- Implement and tune tabular Q-learning
- Structure small simulation environments in a clean, object-oriented style

---

## Project Overview

At a high level, the agent controls a **Charmander** in repeated battles against an **opponent Squirtle**. Over many episodes, the agent learns which move to select in different health configurations to maximize its chance of winning.

Core components:

- **Environment Abstraction**
  - `Pokemon` class encapsulates battle-relevant stats (HP, Attack, Defense, Speed) and available moves.
  - `Move` class captures damage, accuracy, and move type.
  - `BattleWithAgent` simulates turn-based combat between the learning agent and a scripted opponent.

- **RL Agent**
  - `QLearningAgent` maintains a tabular Q-function using a `defaultdict`.
  - State space: `(player.current_hp, opponent.current_hp)`
  - Action space: indices of available moves for the agent’s Pokémon (e.g., `Tackle`, `Ember`).
  - Policy: ε-greedy exploration over learned Q-values.

- **Training Loop**
  - Runs multiple independent episodes (default: 100,000).
  - Re-instantiates fresh Pokémon each episode to reset the environment.
  - Logs periodic progress (win indicator) to stdout.

---

## Technical Details

### State Representation

The agent’s **state** is a tuple:

```python
(player.current_hp, opponent.current_hp)
