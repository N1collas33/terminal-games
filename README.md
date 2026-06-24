# >_ terminal-games 

## 🕹️ Games

### ⌗ Tic-Tac-Toe
The basic Tic-Tac-Toe game with a simple AI opponent.
After the player makes a move, the AI responds automatically.

⭕❌ The AI can:
- Block the player winning move.
- Making the correct move to win.
- Prioritizing the center position.

### ♠️ ♥️ BlackJack
Blackjack is a very popular casino card game. The player (you) and the dealer play against each other, competing to see who will get 21 as the sum of the hand, or get closer to it. Both the player and the dealer receive 2 initial cards, which form the first hand. The dealer's second card is hidden until the player's turn ends. During the player turn, you can hit, to get another card for your hand. However if the total exceeds 21 you bust and lose automatically. You can also stand with your hand, the cycle repeats until you stand or bust. Once you stand or bust, the dealer reveals their hidden card and palys their hand. Like you, they draw cards, but the dealer must hit if their total is 16 or less, and stand on 17 or more.

♦️♣️ Cards Value
- A: 1 or 11 (whichever keeps the hand ≤ 21)
- 2, 3, 4, 5, 6, 7, 8, 9, 10 : Face value
- J, Q, K: 10 

## 🛠️ How to build & run.
gcc game.c -o play
./play
