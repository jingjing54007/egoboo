//********************************************************************************************
//*
//*    This file is part of Egoboo.
//*
//*    Egoboo is free software: you can redistribute it and/or modify it
//*    under the terms of the GNU General Public License as published by
//*    the Free Software Foundation, either version 3 of the License, or
//*    (at your option) any later version.
//*
//*    Egoboo is distributed in the hope that it will be useful, but
//*    WITHOUT ANY WARRANTY; without even the implied warranty of
//*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//*    General Public License for more details.
//*
//*    You should have received a copy of the GNU General Public License
//*    along with Egoboo.  If not, see <http://www.gnu.org/licenses/>.
//*
//********************************************************************************************

/// @file egolib/Script/script_scanner.cpp
/// @brief Token of the PDL (Program Definition Language) of EgoScript.
/// @author Michael Heilmann

#include "game/script_scanner.hpp"

namespace Ego {
namespace Script {

PDLToken::PDLToken()
    : m_lexeme(), m_startLocation("<unknown>", 1), m_value(0), m_kind(Kind::Unknown)
{}

PDLToken::PDLToken(Kind kind, const Id::Location& startLocation, const std::string& lexeme)
    : m_lexeme(lexeme), m_startLocation(startLocation), m_value(0), m_kind(kind)
{}

PDLToken::PDLToken(const PDLToken& other)
    : m_lexeme(other.m_lexeme), m_startLocation(other.m_startLocation), m_value(other.m_value), m_kind(other.m_kind)
{}

PDLToken::~PDLToken()
{}

bool PDLToken::is(PDLToken::Kind kind) const
{
    return kind == getKind();
}

bool PDLToken::isOneOf(PDLToken::Kind kind1, PDLToken::Kind kind2) const
{
    return is(kind1) || is(kind2);
}

bool PDLToken::isOperator() const
{
    return isOneOf(Kind::Assign,
                   Kind::Plus,
                   Kind::Minus,
                   Kind::And,
                   Kind::Multiply,
                   Kind::Divide,
                   Kind::Modulus,
                   Kind::ShiftRight,
                   Kind::ShiftLeft);
}

bool PDLToken::isAssignOperator() const
{
    return is(PDLToken::Kind::Assign);
}

Id::Location PDLToken::getStartLocation() const
{
    return m_startLocation;
}

void PDLToken::setStartLocation(const Id::Location& startLocation)
{
    m_startLocation = startLocation;
}

PDLToken::Kind PDLToken::getKind() const
{
    return m_kind;
}

void PDLToken::setKind(PDLToken::Kind kind)
{
    m_kind = kind;
}

void PDLToken::setLexeme(const std::string& lexeme)
{
    m_lexeme = lexeme;
}

const std::string& PDLToken::getLexeme() const
{
    return m_lexeme;
}

std::ostream& operator<<(std::ostream& os, const PDLToken::Kind& tokenKind)
{
    switch (tokenKind)
    {
    #define Define(enumElementName, string) case PDLToken::Kind::enumElementName: os << string; break;
        Define(Constant, "constant")
        Define(Function, "function")
        Define(Assign, "assign")
        Define(And, "and")
        Define(Plus, "plus")
        Define(Minus, "minus")
        Define(Multiply, "multiply")
        Define(Divide, "divide")
        Define(Modulus, "modulus")
        Define(ShiftRight, "shift right")
        Define(ShiftLeft, "shift left")
        Define(Unknown, "unknown")
        Define(Variable, "variable")
        Define(Name, "name")
        Define(IDSZ, "idsz")
        Define(NumericLiteral, "numeric literal")
        Define(Reference, "reference")
    #undef Define
    };
    return os;
}

std::ostream& operator<<(std::ostream& os, const PDLToken& token)
{
    os << "token {";
    os << "location = " << token.getStartLocation().getFileName() << ":" << token.getStartLocation().getLineNumber() << "," << std::endl;
    os << "value = " << token.getValue() << "," << std::endl;
    os << "type = " << token.getKind() << "," << std::endl;
    os << "text = " << token.getLexeme() << std::endl;
    os << "}" << std::endl;
    return os;
}

} // namespace Script
} // namespace Ego
