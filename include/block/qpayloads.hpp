#pragma once

#include "block/carray.hpp"
#include "block/qunlocks.hpp"
#include <QByteArray>
#include <QDataStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
namespace qiota
{
namespace qblocks
{
class Essence;
class Payload
{
  public:
    enum types : quint32
    {
        Tagged_Data_typ = 5,
        Transaction_typ = 6
    };
    Payload(types type_);
    template <class from_type> static std::shared_ptr<const Payload> from_(from_type &val);

    static std::shared_ptr<const Payload> Tagged_Data(const tagF &tag_m, const dataF &data_m);
    static std::shared_ptr<const Payload> Transaction(const std::shared_ptr<const Essence> &essence_m,
                                                      const pvector<const Unlock> &unlocks_m);

    virtual void serialize(QDataStream &out) const;
    virtual QJsonObject get_Json(void) const;
    virtual c_array get_id(void) const
    {
        return c_array(32, 0);
    };
    types type(void) const
    {
        return type_m;
    }

  private:
    const types type_m;
};

class Tagged_Data_Payload : public Payload
{
  public:
    Tagged_Data_Payload(const tagF &tag_m, const dataF &data_m);
    Tagged_Data_Payload(const QJsonValue &val);
    Tagged_Data_Payload(QDataStream &in);
    void serialize(QDataStream &out) const;

    QJsonObject get_Json(void) const;

  private:
    tagF tag_;
    dataF data_;
};

class Transaction_Payload : public Payload
{
  public:
    Transaction_Payload(const std::shared_ptr<const Essence> &essence_m, const pvector<const Unlock> &unlocks_m);
    Transaction_Payload(const QJsonValue &val);
    Transaction_Payload(QDataStream &in);

    void serialize(QDataStream &out) const;

    QJsonObject get_Json(void) const;
    c_array get_id(void) const;

  private:
    std::shared_ptr<const Essence> essence_;
    pvector<const Unlock> unlocks_;
};
}; // namespace qblocks
}; // namespace qiota
