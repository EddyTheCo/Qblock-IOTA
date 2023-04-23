#pragma once

#include <QByteArray>
#include <QDataStream>
#include <QJsonValue>
#include"block/carray.hpp"
#include"block/qaddresses.hpp"
namespace qiota{
namespace qblocks{
class  Signature
{
public:
    enum types : quint8 {Ed25519_typ=0};
    Signature(types typ );
    template<class from_type> static std::shared_ptr<const Signature> from_(from_type& val);
    template<class deriv, class... Types> static std::shared_ptr<const Signature> get(Types... args)
    {
        return std::shared_ptr<const Signature>(new deriv(args...));
    }
    virtual void serialize(QDataStream &out)const;
    virtual QJsonObject get_Json(void) const;

    types type(void)const{return type_m;}

private:
    const types type_m;

};

class Ed25519_Signature : public Signature
{
public:
    Ed25519_Signature(public_key public_key_m,signature signature_m);
    Ed25519_Signature(const QJsonValue& val);
    Ed25519_Signature(QDataStream &in);
    void serialize(QDataStream &out)const;
    QJsonObject get_Json(void) const;


private:
public_key public_key_;
signature  signature_;

};

};

};
