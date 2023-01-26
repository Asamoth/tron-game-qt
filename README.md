# **2D TRON arcade game in C++ with Qt**

This was a GUI project to familiarize myself with the Qt framework and C++ in general.
The game was coded with Qt MinGW-w64 4.2 and using a different version might cause some issues.

This game of Tron consists of two players who move leaving behind a trail.
Players cannot pass through other walls or any players' trails, including their own.
The object of the game is to get the opponent out of the grid by cutting them off and leading them colliding with any trail, or the walls.
Players can move in all four directions (up, down, left, right) using their keyboard keys.
Both players play on the same keyboard - the first player with the WASD keys, and the second player with the arrow keys on the keyboard.
The winning player is the one who manages to survive the longest.
The game is designed to be played on hard difficulty - other difficulties create some minor display issues when players turn but no real behavior problems.
