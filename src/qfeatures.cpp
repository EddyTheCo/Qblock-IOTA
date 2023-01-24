#include"block/qfeatures.hpp"
namespace qiota{
namespace qblocks{
void Feature::serialize(QDataStream &out)const{};
QJsonObject Feature::get_Json(void) const{return QJsonObject();};
Feature::Feature(types typ ):type_m(typ){};
template<class from_type> std::shared_ptr<Feature> Feature::from_(from_type& val){
    const auto type_=get_type<types>(val);

    switch(type_) {
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
template std::shared_ptr<Feature> Feature::from_<const QJsonValue>(const QJsonValue& val);
template std::shared_ptr<Feature> Feature::from_<QDataStream >(QDataStream & val);
template std::shared_ptr<Feature> Feature::from_<const QJsonValueRef>(const QJsonValueRef& val);


Sender_Feature::Sender_Feature(std::shared_ptr<Address> sender_m):Feature(Sender_typ),sender_(sender_m){};
Sender_Feature::Sender_Feature(const QJsonValue& val):Sender_Feature(Address::from_<const QJsonValue>(val.toObject()["address"])){};
Sender_Feature::Sender_Feature(QDataStream &in):Feature(Sender_typ),sender_(Address::from_<QDataStream>(in)){};
void Sender_Feature::serialize(QDataStream &out)const
{
    out<<type_m;
    sender_->serialize(out);
}
QJsonObject Sender_Feature::get_Json(void) const
{
    QJsonObject var;
    var.insert("type",(int)type_m);
    var.insert("address",sender_->get_Json());
    return var;
}

Issuer_Feature::Issuer_Feature(std::shared_ptr<Address> issuer_m):Feature(Issuer_typ),issuer_(issuer_m){};
Issuer_Feature::Issuer_Feature(const QJsonValue& val):Issuer_Feature(Address::from_<const QJsonValue>(val.toObject()["address"])){};
Issuer_Feature::Issuer_Feature(QDataStream &in):Feature(Issuer_typ),issuer_(Address::from_<QDataStream>(in)){};
void Issuer_Feature::serialize(QDataStream &out)const
{
    out<<type_m;
    issuer_->serialize(out);
}
QJsonObject Issuer_Feature::get_Json(void) const
{
    QJsonObject var;
    var.insert("type",(int)type_m);
    var.insert("address",issuer_->get_Json());
    return var;
}

Metadata_Feature::Metadata_Feature(fl_array<quint16> data_m):Feature(Metadata_typ),data_(data_m){};
Metadata_Feature::Metadata_Feature(const QJsonValue& val):Metadata_Feature(fl_array<quint16>(val.toObject()["data"])){};
Metadata_Feature::Metadata_Feature(QDataStream &in):Feature(Metadata_typ){
    in>>data_;
};
void Metadata_Feature::serialize(QDataStream &out)const
{
    out<<type_m;
    out<<data_;
}
QJsonObject Metadata_Feature::get_Json(void) const
{
    QJsonObject var;
    var.insert("type",(int)type_m);
    var.insert("data",data_.toHexString());
    return var;
}
Tag_Feature::Tag_Feature(fl_array<quint8> tag_m):Feature(Tag_typ),tag_(tag_m){};
Tag_Feature::Tag_Feature(const QJsonValue& val):Tag_Feature(fl_array<quint8>(val.toObject()["tag"])){};
Tag_Feature::Tag_Feature(QDataStream &in):Feature(Tag_typ){
    in>>tag_;
};
void Tag_Feature::serialize(QDataStream &out)const
{
    out<<type_m;
    out<<tag_;
}
QJsonObject Tag_Feature::get_Json(void) const
{
    QJsonObject var;
    var.insert("type",(int)type_m);
    var.insert("tag",tag_.toHexString());
    return var;
}
};
};
