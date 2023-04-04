#pragma once


#include"block/carray.hpp"
#include<QJsonObject>
namespace qiota{
namespace qblocks{

class  Address
{
public:
    enum types : quint8 { NFT_typ=16, Alias_typ=8, Ed25519_typ=0};

    Address(types typ, c_array addrhash_m );
    Address(types typ,QDataStream &in);
    template<class from_type> static std::shared_ptr<Address> from_(from_type& val);
    static std::shared_ptr<Address> from_(QByteArray& val);
    static std::shared_ptr<Address> from_(c_array& val)
    {
        auto var=QByteArray(val.constData(),val.size());
        return from_(var);
    };


    virtual void serialize(QDataStream &out)const;
    virtual QJsonObject get_Json(void) const;
    c_array addrhash(void)const{return addrhash_;}
    c_array addr(void)const{
        c_array addr;
        auto buffer=QDataStream(&addr,QIODevice::WriteOnly | QIODevice::Append);
        buffer.setByteOrder(QDataStream::LittleEndian);
        serialize(buffer);
        return addr;}

    types type(void)const{return type_m;}

private:
    const types type_m;
    c_array addrhash_;

};

class NFT_Address : public Address
{
public:
    NFT_Address(c_array nft_id_m);
    NFT_Address(const QJsonValue& val);
    NFT_Address(QDataStream &in);

    QJsonObject get_Json(void) const;

};
class Alias_Address : public Address
{
public:
    Alias_Address(c_array alias_id_m);
    Alias_Address(const QJsonValue& val);
    Alias_Address(QDataStream &in);

    QJsonObject get_Json(void) const;

};

class Ed25519_Address : public Address
{
public:
    Ed25519_Address(c_array pubkeyhash_m);
    Ed25519_Address(const QJsonValue& val);
    Ed25519_Address(QDataStream &in);

    QJsonObject get_Json(void) const;

};

};
};
