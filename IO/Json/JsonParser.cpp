// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "JsonParser.h"

#include <charconv>

utils::Result<io::JsonValue> io::JsonParser::parse() {
    char ch = peek();
    if (!ch) {
        return utils::Failure("End of string met while parsing");
    }

    if (ch == '{') {
        return parseObject();
    } else if (ch == '[') {
        return parseArray();
    } else if (ch == '"') {
        return parseString();
    } else if (isdigit(ch) || ch == '-') {
        return parseNumber();
    } else if (isalpha(ch)) {
        return parseWord();
    }

    return utils::Failure("Unknown value");
}

utils::Result<io::JsonValue> io::JsonParser::parseObject() {
    next(); // skip {
    skipWS();

    if (peek() == '}') { // empty object
        next();

        return io::JsonValue(io::JsonValue::ObjectTy());
    }

    io::JsonValue::ObjectTy result;
    auto isDuplicate = [&result](const std::string& str) -> bool {
        for (auto& p : result) {
            if (p.first == str) {
                return true;
            }

            return false;
        }
    };

    do {
        skipWS();
        auto key = parseString();
        if (!key.isOk()) {
            return key;
        } else if (isDuplicate(key.value().asString())) {
            return utils::Failure("Json object: a duplicate key: " + key.value().asString());
        }
        

        skipWS();
        if (peek() != ':') {
            return utils::Failure("No : after a key in an object");
        }

        next();
        skipWS();

        auto val = parse();
        if (!val.isOk()) {
            return val;
        }

        result.emplace_back(key.extract().asString(), val.extract());
    } while (peek() == ',' && next());

    skipWS();
    if (peek() != '}') {
        return utils::Failure("No closing }");
    }

    next();
    return io::JsonValue(std::move(result));
}

utils::Result<io::JsonValue> io::JsonParser::parseArray() {
    next(); // skip [
    skipWS();

    if (peek() == ']') { // empty array
        next();

        return io::JsonValue(std::vector<io::JsonValue>());
    }

    std::vector<io::JsonValue> vec;
    do {
        skipWS();
        auto val = parse();
        if (!val.isOk()) {
            return val;
        }

        vec.push_back(val.extract());
    } while (peek() == ',' && next());

    skipWS();
    if (peek() != ']') {
        return utils::Failure("No closing ]");
    }

    next();
    return io::JsonValue(std::move(vec));
}

utils::Result<io::JsonValue> io::JsonParser::parseString() {
    next(); // skip the first "

    std::string tmp;
    while (peek() != '"' && peek() != '\n' && peek() != '\r') {
        char ch = peek();

        if (ch == '\\') {
            next();
            ch = peek();

            switch (ch) {
                case '\\': break;
                case '"': break;
                case 'n': ch = '\n'; break;
                case 't': ch = '\t'; break;
                case 'v': ch = '\v'; break;
                case 'r': ch = '\r'; break;
                case 'f': ch = '\f'; break;
                case 'a': ch = '\a'; break;
                case 'b': ch = '\b'; break;
            default: return utils::Failure("Unknown escape sequence: \\" + ch);
            }
        }

        tmp += ch;

        if (!next()) {
            break;
        }
    }

    if (peek() != '"') {
        return utils::Failure("No closing \"");
    }

    next(); // skip the second "

    return io::JsonValue(std::move(tmp));
}

utils::Result<io::JsonValue> io::JsonParser::parseNumber() {
    size_t pos = m_pos;
    bool m_isFP = false;

    do {
        if (isdigit(peek()) || peek() == '-') {
            continue;
        } else if (peek() == '.' || peek() == 'e' || peek() == 'E') {
            m_isFP = true;
            continue;
        }

        break;
    } while (next());

    if (!m_isFP) {
        intmax_t result;
        std::string_view intView = m_text.substr(pos, m_pos - pos);
        auto convResult = std::from_chars(intView.data(), intView.data() + intView.size(), result);

        if (convResult.ec != std::errc()) {
            return utils::Failure("Invalid number: " + std::string(intView));
        }

        return io::JsonValue(result);
    } else {
        double result;
        std::string_view intView = m_text.substr(pos, m_pos - pos);
        auto convResult = std::from_chars(intView.data(), intView.data() + intView.size(), result);

        if (convResult.ec != std::errc()) {
            return utils::Failure("Invalid number: " + std::string(intView));
        }

        return io::JsonValue(result);
    }
}

utils::Result<io::JsonValue> io::JsonParser::parseWord() {
    size_t pos = m_pos;
    while (isalpha(peek()) && next());

    std::string_view word = m_text.substr(pos, m_pos - pos);
    if (word == "true") {
        return io::JsonValue(utils::Tribool(true));
    } else if (word == "false") {
        return io::JsonValue(utils::Tribool(false));
    } else if (word == "null") {
        return io::JsonValue(utils::Tribool());
    }

    return utils::Failure("Expected either of [true, false, null], got: " + std::string(word));
}

void io::JsonParser::skipWS() {
    while (isspace(peek()) && next());
}

bool io::JsonParser::match(char ch) {
    if (peek() == ch) {
        next();
        return true;
    }

    return false;
}

char io::JsonParser::next() {
    if (m_pos >= m_text.size()) {
        return '\0';
    }

    return m_text[m_pos++];
}

char io::JsonParser::peek(int32_t relPos) {
    if (m_pos + relPos >= m_text.size()) {
        return '\0';
    }

    return m_text[m_pos + relPos];
}
