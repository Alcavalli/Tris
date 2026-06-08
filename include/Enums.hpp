enum class GameStatus
{
    InProgress,
    Player1Win,             //* win player 1
    Player2Win,             //* win player 2
    Draw
};

enum class CellStatus
{
    Empty,
    Player1,                //* player 1 symbol
    Player2                 //* player 2 symbol
};

enum class GameMode
{
    PvP,                    //* Player vs Player
    PvE                     //* Player vs AI
};

enum class Difficulty       //* PvE
{
    Easy,
    Medium,
    Hard
};