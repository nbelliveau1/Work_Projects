
import random
from collections import defaultdict

# --- Move and Pokemon Classes ---

class Move:
    def __init__(self, name, damage, accuracy, move_type):
        self.name = name
        self.damage = damage
        self.accuracy = accuracy
        self.move_type = move_type

class Pokemon:
    def __init__(self, name, hp, attack, defense, speed, moves):
        self.name = name
        self.max_hp = hp
        self.current_hp = hp
        self.attack = attack
        self.defense = defense
        self.speed = speed
        self.moves = moves

    def is_fainted(self):
        return self.current_hp <= 0

    def take_damage(self, damage):
        self.current_hp = max(self.current_hp - damage, 0)


# --- Q-Learning Agent ---

class QLearningAgent:
    def __init__(self, actions, alpha=0.1, gamma=0.9, epsilon=0.2):
        self.q_table = defaultdict(lambda: [0.0] * len(actions))
        self.actions = actions
        self.alpha = alpha
        self.gamma = gamma
        self.epsilon = epsilon

    def get_state(self, player, opponent):
        return (player.current_hp, opponent.current_hp)

    def choose_action(self, state):
        if random.random() < self.epsilon:
            return random.choice(self.actions)
        else:
            q_values = self.q_table[state]
            max_value = max(q_values)
            # If multiple actions have the same max value, randomly choose among them
            max_actions = [i for i, q in enumerate(q_values) if q == max_value]
            return random.choice(max_actions)

    def update(self, state, action, reward, next_state):
        best_next = max(self.q_table[next_state])
        self.q_table[state][action] += self.alpha * (reward + self.gamma * best_next - self.q_table[state][action])


# --- Battle Simulator ---

class BattleWithAgent:
    def __init__(self, agent, pokemon1, pokemon2):
        self.agent = agent
        self.p1 = pokemon1  # Agent's Pokémon
        self.p2 = pokemon2  # Opponent

    def simulate_battle(self):
        state = self.agent.get_state(self.p1, self.p2)

        while not self.p1.is_fainted() and not self.p2.is_fainted():
            action_idx = self.agent.choose_action(state)
            move = self.p1.moves[action_idx]

            # Agent attacks
            if random.random() <= move.accuracy:
                damage = max(1, move.damage + self.p1.attack - self.p2.defense)
                self.p2.take_damage(damage)

            # Reward setting
            reward = 0
            if self.p2.is_fainted():
                reward = 1
            elif self.p1.is_fainted():
                reward = -1

            next_state = self.agent.get_state(self.p1, self.p2)
            self.agent.update(state, action_idx, reward, next_state)
            state = next_state

            # Opponent attacks if not fainted
            if not self.p2.is_fainted():
                opp_move = random.choice(self.p2.moves)
                if random.random() <= opp_move.accuracy:
                    damage = max(1, opp_move.damage + self.p2.attack - self.p1.defense)
                    self.p1.take_damage(damage)

        return 1 if self.p2.is_fainted() else 0


# --- Main Training Script ---

def main():
    tackle = Move("Tackle", damage=10, accuracy=1.0, move_type="Normal")
    ember = Move("Ember", damage=12, accuracy=0.9, move_type="Fire")

    actions = [0, 1]
    agent = QLearningAgent(actions)

    for episode in range(100000):
        charmander = Pokemon("Charmander", 35, 15, 10, 14, [tackle, ember])
        squirtle = Pokemon("Squirtle", 40, 13, 12, 12, [tackle])

        battle = BattleWithAgent(agent, charmander, squirtle)
        result = battle.simulate_battle()

        if episode % 100 == 0:
            print(f"Episode {episode}: Win={result}")

    print("Training complete.")

if __name__ == "__main__":
    main()
