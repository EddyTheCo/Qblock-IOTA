
#include"block/qunlocks.hpp"
namespace qiota{
namespace qblocks{
void Unlock::serialize(QDataStream &out)const{};
QJsonObject Unlock::get_Json(void) const{return QJsonObject();};
Unlock::Unlock(quint8 typ ):type_m(typ){};

template<typename from_type> std::shared_ptr<Unlock> Unlock::from_(from_type& val){
    const auto type_=get_type<quint8>(val);

    switch(type_) {
    case 0:
        return std::shared_ptr<Unlock>(new Signature_Unlock(val));
    case 1:
        return std::shared_ptr<Unlock>(new Reference_Unlock(val));
    case 2:
        return std::shared_ptr<Unlock>(new Alias_Unlock(val));
    case 3:
        return std::shared_ptr<Unlock>(new NFT_Unlock(val));
    default:
        return nullptr;
    }
}

template std::shared_ptr<Unlock> Unlock::from_<const QJsonValue>(const QJsonValue& val);
template std::shared_ptr<Unlock> Unlock::from_<QDataStream>(QDataStream & val);
template std::shared_ptr<Unlock> Unlock::from_<const QJsonValueRef>(const QJsonValueRef& val);


Signature_Unlock::Signature_Unlock(const std::shared_ptr<Signature> &signature_m):Unlock(0),signature_(signature_m){};
Signature_Unlock::Signature_Unlock(const QJsonValue& val):Signature_Unlock(Signature::from_<const QJsonValue>(val.toObject()["signature"])){};
Signature_Unlock::Signature_Unlock(QDataStream &in):Unlock(0),signature_(Signature::from_<QDataStream>(in)){};
void Signature_Unlock::serialize(QDataStream &out)const
{
    out<<type_m;
    signature_->serialize(out);
}
QJsonObject Signature_Unlock::get_Json(void) const
{
    QJsonObject var;
    var.insert("type",(int)type_m);
    var.insert("signature",signature_->get_Json());
    return var;
}

Reference_Unlock::Reference_Unlock(quint16 reference_m):Unlock(1),reference_(reference_m){};
Reference_Unlock::Reference_Unlock(const QJsonValue& val):Reference_Unlock(val.toObject()["reference"].toInt()){};
Reference_Unlock::Reference_Unlock(QDataStream &in):Unlock(1)
{
    in>>reference_;
}
void Reference_Unlock::serialize(QDataStream &out)const
{
    out<<type_m;
    out<<reference_;
}
QJsonObject Reference_Unlock::get_Json(void) const
{
    QJsonObject var;
    var.insert("type",(int)type_m);
    var.insert("reference",(int)reference_);
    return var;
}

Alias_Unlock::Alias_Unlock(quint16 alias_reference_unlock_index_m):Unlock(2),alias_reference_unlock_index_(alias_reference_unlock_index_m){};
Alias_Unlock::Alias_Unlock(const QJsonValue& val):Alias_Unlock(val.toObject()["reference"].toInt()){};
Alias_Unlock::Alias_Unlock(QDataStream &in):Unlock(2)
{
    in>>alias_reference_unlock_index_;
}
void Alias_Unlock::serialize(QDataStream &out)const
{
    out<<type_m;
    out<<alias_reference_unlock_index_;
}
QJsonObject Alias_Unlock::get_Json(void) const
{
    QJsonObject var;
    var.insert("type",(int)type_m);
    var.insert("reference",(int)alias_reference_unlock_index_);
    return var;
}


NFT_Unlock::NFT_Unlock(quint16 nft_reference_unlock_index_m):Unlock(3),nft_reference_unlock_index_(nft_reference_unlock_index_m){};
NFT_Unlock::NFT_Unlock(const QJsonValue& val):NFT_Unlock(val.toObject()["reference"].toInt()){};
NFT_Unlock::NFT_Unlock(QDataStream &in):Unlock(3)
{
    in>>nft_reference_unlock_index_;
}
void NFT_Unlock::serialize(QDataStream &out)const
{
    out<<type_m;
    out<<nft_reference_unlock_index_;
}
QJsonObject NFT_Unlock::get_Json(void) const
{
    QJsonObject var;
    var.insert("type",(int)type_m);
    var.insert("reference",(int)nft_reference_unlock_index_);
    return var;
}
};
};
