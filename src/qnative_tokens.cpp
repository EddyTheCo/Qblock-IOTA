#include "block/qnative_tokens.hpp"
namespace qiota
{
namespace qblocks
{
std::shared_ptr<const Native_Token> Native_Token::Native(const Token_ID &token_id_m, const quint256 &amount_m)
{
    return std::shared_ptr<Native_Token>(new Native_Token(token_id_m, amount_m));
}

Native_Token::Native_Token(const Token_ID &token_id_m, const quint256 &amount_m)
    : token_id_(token_id_m), amount_(amount_m){};
Native_Token::Native_Token(const QJsonValue &val)
    : token_id_(Token_ID(val.toObject()["id"])), amount_(quint256(val.toObject()["amount"].toString())){};

template <class from_type> std::shared_ptr<const Native_Token> Native_Token::from_(from_type &val)
{
    return std::shared_ptr<Native_Token>(new Native_Token(val));
}

template std::shared_ptr<const Native_Token> Native_Token::from_<const QJsonValue>(const QJsonValue &val);
template std::shared_ptr<const Native_Token> Native_Token::from_<QDataStream>(QDataStream &val);
template std::shared_ptr<const Native_Token> Native_Token::from_<const QJsonValueRef>(const QJsonValueRef &val);
template std::shared_ptr<const Native_Token> Native_Token::from_<QJsonValueConstRef const>(QJsonValueConstRef const &);

Native_Token::Native_Token(QDataStream &in)
{
    token_id_ = c_array(38, 0);
    in >> token_id_;
    in >> amount_;
};

void Native_Token::serialize(QDataStream &out) const
{
    out << token_id_;
    out << amount_;
}
QJsonObject Native_Token::get_Json(void) const
{
    QJsonObject var;
    var.insert("id", token_id_.toHexString());
    var.insert("amount", amount_.toHex());
    return var;
}

}; // namespace qblocks

}; // namespace qiota
