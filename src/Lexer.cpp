#include "Lexer.h"

// Lexical Analysis

namespace charinfo {
    LLVM_READNONE inline bool isWhiteSpace(char c) {
        return c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r' || c == '\n';
    }
    LLVM_READNONE inline bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }
    LLVM_READNONE inline bool isLetter(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
}

void Lexer::next(Token &token) {
    while (*BufferPtr && charinfo::isWhiteSpace(*BufferPtr)) {
        ++BufferPtr;
    }

    if (!*BufferPtr) {
        token.Kind = Token::eoi;
        return;
    }

    if (charinfo::isLetter(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while (charinfo::isLetter(*end)) ++end;
        llvm::StringRef Name(BufferPtr, end - BufferPtr);
        Token::TokenKind kind = (Name == "with") ? Token::KW_with : Token::ident;
        formToken(token, end, kind);
        return;
    } else if (charinfo::isDigit(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while (charinfo::isDigit(*end)) ++end;
        formToken(token, end, Token::number);
        return;
    } else {
        switch (*BufferPtr) {
            #define CASE(ch, tok) case ch: formToken(token, BufferPtr + 1, tok); break
            CASE('+', Token::TokenKind::plus);
            CASE('-', Token::TokenKind::minus);
            CASE('*', Token::TokenKind::star);
            CASE('/', Token::TokenKind::slash);
            CASE('(', Token::TokenKind::l_paren);
            CASE(')', Token::TokenKind::r_paren);
            CASE(':', Token::TokenKind::colon);
            CASE(',', Token::TokenKind::comma);
            #undef CASE
            default:
                formToken(token, BufferPtr + 1, Token::TokenKind::unknown);
        }
        return;
    }
}

void Lexer::formToken(Token &Tok, const char *TokEnd, Token::TokenKind Kind) {
    Tok.Kind = Kind;
    Tok.Text = llvm::StringRef(BufferPtr, TokEnd - BufferPtr);
    BufferPtr = TokEnd;
}