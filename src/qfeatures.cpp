#include "block/qfeatures.hpp"
namespace qiota
{
namespace qblocks
{

const QHash<Feature::types, QString> Feature::typesstr = {
    {Sender_typ, "address"}, {Issuer_typ, "address"}, {Metadata_typ, "data"}, {Tag_typ, "tag"}};

void Feature::serialize(QDataStream &out) const {};
QJsonObject Feature::get_Json(void) const
{
    return QJsonObject();
};
Feature::Feature(types typ) : type_m(typ){};
template <class from_type> std::shared_ptr<const Feature> Feature::from_(from_type &val)
{
    const auto type_ = get_type<types>(val);

    switch (type_)
    {
    case Metadata_typ:
        return std::shared_ptr<Feature>(new Metadata_Feature(val));
    case Tag_typ:
        return std::shared_ptr<Feature>(new Tag_Feature(val));
    case Sender_typ:
        return std::shared_ptr<Feature>(new Sender_Feature(val));
    case Issuer_typ:
        return std::shared_ptr<Feature>(new Issuer_Feature(val));
    default:
        return nullptr;
    }
}
template std::shared_ptr<const Feature> Feature::from_<const QJsonValue>(const QJsonValue &val);
template std::shared_ptr<const Feature> Feature::from_<QDataStream>(QDataStream &val);
template std::shared_ptr<const Feature> Feature::from_<const QJsonValueRef>(const QJsonValueRef &val);
template std::shared_ptr<const Feature> Feature::from_<QJsonValueConstRef const>(QJsonValueConstRef const &);

std::shared_ptr<const Feature> Feature::Sender(const std::shared_ptr<const Address> &sender_m)
{
    return std::shared_ptr<Feature>(new Sender_Feature(sender_m));
}

Sender_Feature::Sender_Feature(const std::shared_ptr<const Address> &sender_m)
    : Feature(Sender_typ), sender_(sender_m){};
Sender_Feature::Sender_Feature(const QJsonValue &val)
    : Sender_Feature(Address::from_<const QJsonValue>(val.toObject()["address"])){};
Sender_Feature::Sender_Feature(QDataStream &in) : Feature(Sender_typ), sender_(Address::from_<QDataStream>(in)){};
void Sender_Feature::serialize(QDataStream &out) const
{
    out << type();
    sender_->serialize(out);
}
QJsonObject Sender_Feature::get_Json(void) const
{
    QJsonObject var;
    var.insert("type", (int)type());
    var.insert("address", sender_->get_Json());
    return var;
}
std::shared_ptr<const Feature> Feature::Issuer(const std::shared_ptr<const Address> &issuer_m)
{
    return std::shared_ptr<Feature>(new Issuer_Feature(issuer_m));
}
Issuer_Feature::Issuer_Feature(const std::shared_ptr<const Address> &issuer_m)
    : Feature(Issuer_typ), issuer_(issuer_m){};
Issuer_Feature::Issuer_Feature(const QJsonValue &val)
    : Issuer_Feature(Address::from_<const QJsonValue>(val.toObject()["address"])){};
Issuer_Feature::Issuer_Feature(QDataStream &in) : Feature(Issuer_typ), issuer_(Address::from_<QDataStream>(in)){};
void Issuer_Feature::serialize(QDataStream &out) const
{
    out << type();
    issuer_->serialize(out);
}
QJsonObject Issuer_Feature::get_Json(void) const
{
    QJsonObject var;
    var.insert("type", (int)type());
    var.insert("address", issuer_->get_Json());
    return var;
}

std::shared_ptr<const Feature> Feature::Metadata(const fl_array<quint16> &data_m)
{
    return std::shared_ptr<Feature>(new Metadata_Feature(data_m));
}

Metadata_Feature::Metadata_Feature(const fl_array<quint16> &data_m) : Feature(Metadata_typ), data_(data_m){};
Metadata_Feature::Metadata_Feature(const QJsonValue &val)
    : Metadata_Feature(fl_array<quint16>(val.toObject()["data"])){};
Metadata_Feature::Metadata_Feature(QDataStream &in) : Feature(Metadata_typ)
{
    in >> data_;
};
void Metadata_Feature::serialize(QDataStream &out) const
{
    out << type();
    out << data_;
}
QJsonObject Metadata_Feature::get_Json(void) const
{
    QJsonObject var;
    var.insert("type", (int)type());
    var.insert("data", data_.toHexString());
    return var;
}
std::shared_ptr<const Feature> Feature::Tag(const fl_array<quint8> &tag_m)
{
    return std::shared_ptr<Feature>(new Tag_Feature(tag_m));
}

Tag_Feature::Tag_Feature(const fl_array<quint8> &tag_m) : Feature(Tag_typ), tag_(tag_m){};
Tag_Feature::Tag_Feature(const QJsonValue &val) : Tag_Feature(fl_array<quint8>(val.toObject()["tag"])){};
Tag_Feature::Tag_Feature(QDataStream &in) : Feature(Tag_typ)
{
    in >> tag_;
};
void Tag_Feature::serialize(QDataStream &out) const
{
    out << type();
    out << tag_;
}
QJsonObject Tag_Feature::get_Json(void) const
{
    QJsonObject var;
    var.insert("type", (int)type());
    var.insert("tag", tag_.toHexString());
    return var;
}
}; // namespace qblocks
}; // namespace qiota
