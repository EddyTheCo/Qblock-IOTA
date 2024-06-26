#pragma once

#include "block/carray.hpp"
#include <QByteArray>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonValue>
namespace qiota
{
namespace qblocks
{
class Input
{
  public:
    enum types : quint8
    {
        UTXO_typ = 0
    };
    Input(types typ);
    template <class from_type> static std::shared_ptr<const Input> from_(from_type &val);

    static std::shared_ptr<const Input> UTXO(const Transaction_ID &transaction_id_m,
                                             const quint16 &transaction_output_index_m);
    virtual void serialize(QDataStream &out) const;
    virtual QJsonObject get_Json(void) const;

    types type(void) const
    {
        return type_m;
    }

  private:
    const types type_m;
};

/*
 * @brief Describes an input which references an unspent transaction output to consume.
 *
 */
class UTXO_Input : public Input
{
  public:
    UTXO_Input(const Transaction_ID &transaction_id_m, const quint16 &transaction_output_index_m);
    UTXO_Input(const QJsonValue &val);
    UTXO_Input(QDataStream &in);
    void serialize(QDataStream &out) const;
    QJsonObject get_Json(void) const;

  private:
    quint16 transaction_output_index_;
    Transaction_ID transaction_id_;
};

}; // namespace qblocks

}; // namespace qiota
