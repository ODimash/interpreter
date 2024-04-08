enum class TokenType {

    Identifier,

    Addition,
    Subtraction,
    Multiplication,
    Division,
    IntegerDivision,
    Modulus,

    Assign,

    AdditionAssignment,
    SubtractionAssignment,
    ConcatenationAssignment,
    MultiplicationAssignment,
    DivisionAssignment,
    IntegerDivisionAssignment,
    ModulusAssignment,

    LogicalNot,
    LogicalAnd,
    LogicalOr,

    Equal,
    NotEqual,
    LessThan,
    GreaterThan,
    LessThanOrEqual,
    GreaterThanOrEqual,

    Comma,
    Colon,

    OpenParen,
    CloseParen,

    OpenBrace,
    CloseBrace,

    OpenBracket,
    CloseBracket,

    Insert,

    KeywordIf,
    KeywordElse,
    KeywordElif,

    KeywordSwitch,
    KeywordDefault,

    KeywordWhile,
    KeywordLoop,

    KeywordStop,
    KeywordSkip,
    KeywordReturn,

    KeywordFnc,

    ValueString,
    ValueNumber,
    ValueHexNumber,
    ValueBinNumber,
    Comment,

    Invalid,
    EndLine,
    EndFile,
};