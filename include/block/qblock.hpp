#pragma once
/**
*
*  https://github.com/iotaledger/tips/blob/main/tips/TIP-0024/tip-0024.md
*
**/

#include <QByteArray>
#include <QDataStream>
#include <QJsonValue>
#include<QJsonObject>
#include<QJsonArray>
#include "block/carray.hpp"
#include "block/qsignatures.hpp"
#include "block/qsignatures.hpp"
#include "block/qpayloads.hpp"
#include "block/qunlocks.hpp"
#include "block/qessences.hpp"
#include "block/qinputs.hpp"
#include "block/qoutputs.hpp"
#include "block/qnative_tokens.hpp"
#include "block/qunlock_conditions.hpp"
#include "block/qfeatures.hpp"
#include "block/qaddresses.hpp"
#include "block/qoutput_metadata_response.hpp"

namespace qiota{

namespace qblocks{
class Block
{
public: 
	Block(){};
    Block(QDataStream &serialized_block);
    Block(const std::shared_ptr<Payload>& pyl);
    Block(const QJsonValue& val);

    friend QDataStream & operator < (QDataStream &out, const Block & obj);
    static QByteArray get_inputs_Commitment(QByteArray Inputs_hash);

    void serialize(QDataStream &out)const;

    QJsonObject get_Json(void)const;

    void set_parents(const std::vector<Block_ID>& parents_m);

    void set_nonce(const quint64& nonce_m);
    void set_pv(const quint8& pv);
    std::shared_ptr<const Payload> payload()const{return payload_;}
    private:

    quint8 protocol_version;
    quint64 nonce_;
    std::shared_ptr<const Payload> payload_;
    std::vector<Block_ID> parents_;

};

};
};
