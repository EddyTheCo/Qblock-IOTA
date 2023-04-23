#pragma once

#include <QByteArray>
#include <QDataStream>
#include <QJsonValue>
#include<QJsonObject>
#include<QJsonArray>
#include"block/carray.hpp"
#include"block/qoutputs.hpp"
#include"block/qinputs.hpp"


namespace qiota{
namespace qblocks{

class Payload;

class Transaction_Essence;

class  Essence
{
public:
    enum types : quint8 { Transaction_typ=1};
    Essence(types typ );
    template<class from_type> static std::shared_ptr<const Essence> from_(from_type& val);
    template<class deriv, class... Types> static std::shared_ptr<const Essence> get(Types... args)
    {
        return std::shared_ptr<Essence>(new deriv(args...));
    }
    virtual void serialize(QDataStream &out)const;
    virtual QJsonObject get_Json(void) const;

    types type(void)const{return type_m;}
    QByteArray get_hash(void)const;
private:
    const types type_m;

};

class Transaction_Essence : public Essence
{
public:
    Transaction_Essence(const quint64 &network_id_m, const std::vector<std::shared_ptr<const Input>>& inputs_m,
                        const c_array &inputs_commitment_m,
                        const std::vector<std::shared_ptr<const Output>> &outputs_m,
                        const std::shared_ptr<const Payload> &payload_m=nullptr);
    Transaction_Essence(const QJsonValue& val);
    Transaction_Essence(QDataStream &in);
    void serialize(QDataStream &out)const;
    QJsonObject get_Json(void) const;


private:
    quint64 network_id_;                   //The unique value denoting whether the block was meant for mainnet, shimmer, testnet, or a private network.
    std::vector<std::shared_ptr<const Input>> inputs_;
    c_array inputs_commitment_;          //BLAKE2b-256 hash serving as a commitment to the serialized outputs referenced by Inputs.
    std::vector<std::shared_ptr<const Output>> outputs_;
    std::shared_ptr<const Payload> payload_;

};


};
};
