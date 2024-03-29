# Chessbot
A bot to play chess. This is a research project for my course Gameplay Programming 1 at DAE. It is made in the Programming 1 framework.

# How does it work?
## Board representation
For the representation of the board I used a technique called bitboards. With bitboards we use the property of the chess board having 8 rows and 8 columns - so 64 squares - to represent it using one 64 bit number. Now each square is represented with one bit, but we don't know which piece the bit represents. So we will need separate bitboards for each piece type and color. The main benefit of using bitboards is that modern x64 systems can easily check it's state in one operation using bitwise operators. [see implementation](https://github.com/VictorGhys/Chessbot/blob/master/chessbot/Bitboard.cpp)
## Move generation
For the move generation, I can easily pre calculate the king and knight moves for each position and store these in arrays of bitboards. I then use these to calculate the moves faster. 
The moves of the sliding pieces (bishop, rook, queen) are trickier to pre calculate, because they can go along their line until there is a blocking piece. So for these pieces I pre calculate the attack rays in all directions for each position and also store these in bitboards. If there is a piece in the way, we need to do a bitscan forward to find the first bit that is set to one after our sliding piece, which is the blocking piece. We then subtract the attack ray from the blocking piece in the same direction from the normal moves without blocking pieces. Furthermore I also take into account special moves such as "en passant" for which I need to keep track of the last move and "castling" for which I need to keep track of the pieces that haven't moved yet. [see implementation](https://github.com/VictorGhys/Chessbot/blob/master/chessbot/Position.cpp#L455)
## Evaluation
My evaluation function is kept pretty simple and consists of two parts. The first part is the white pieces minus the black pieces which are weighted according to their value. The second part is the mobility of the piece where pieces get a higher value if they are on good squares. To get a good evaluation we need to make sure there aren't any winning strategies in the position before we evaluate. We can do this by first doing all the possible captures of the position to make it more "quiet". I we don't do this you might think that you have a good position after having caught a pawn with your queen. But not realize that your opponent on the next move could just take the queen. To combat this effect called the "horizon effect" we need to first have a quiet position and then evaluate it. [see implementation](https://github.com/VictorGhys/Chessbot/blob/master/chessbot/Position.cpp#L118)
## Find the best move
To find the best move I used the negamax search algorithm with alpha beta pruning. This works by making a game tree with as root the current position which is extend with all the possible moves. It keeps extending every possible move with all the next possible moves and keeps doing this until we reach a specified depth. Then it uses our evaluation function to evaluate the position. I use the properties that white has to maximize it's score to win and that black has to minimize it's score to win together with max(a, b) == -min(-a, -b) to bubble the score back up towards the root node. We then play the move with the best score. The alpha and beta values represent the minimum score that the maximizing player is assured of and the maximum score that the minimizing player is assured of respectively. This is used to skip the evaluation of positions that are really good for one side, but you know that the other player won't allow you to have, because he already has a better move. This eliminates the need to search large portions of the game tree and significantly speeds up the search for the best move. [see implementation](https://github.com/VictorGhys/Chessbot/blob/master/chessbot/Game.cpp#L945)
# Result
![result](./chessbot.gif)
# Conclusion
Although this bot is very basic compared to the best chess engines today, I'm satisfied because it is still a daring opponent for me. A project like this will never be really finished, because there will always be ways to improve the engine and it's performance. So as long as I can't beat it on full strength, I could better focus on improving my own performance. 
## Sources
#### Board representation
- https://en.wikipedia.org/wiki/Bitboard#Chess_bitboards
#### Move generation 
- https://rhysre.net/fast-chess-move-generation-with-magic-bitboards.html
#### Evaluation
- https://www.chessprogramming.org/Simplified_Evaluation_Function
- https://www.chessprogramming.org/Quiescence_Search
#### Find the best move
- https://www.chessprogramming.org/Negamax
- https://www.chessprogramming.org/Alpha-Beta
