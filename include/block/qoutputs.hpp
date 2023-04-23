#pragma once

#include <QByteArray>
#include <QDataStream>
#include <QJsonValue>
#include<QJsonObject>
#include<QJsonArray>
#include"block/carray.hpp"
#include"block/qunlock_conditions.hpp"
#include"block/qfeatures.hpp"
#include"block/qnative_tokens.hpp"
#include"block/qtoken_scheme.hpp"
namespace qiota{
namespace qblocks{

class Output
{
public:
    enum types : quint8 { Basic_typ=3,NFT_typ=6,Foundry_typ=5,Alias_typ=4 };
    Output(types typ,quint64 amount_m, const std::vector<std::shared_ptr<const Unlock_Condition>> & unlock_conditions_m,
           const std::vector<std::shared_ptr<const Feature>>& features_m={},
           const std::vector<std::shared_ptr<const Native_Token>>& native_tokens_m={},
           const std::vector<std::shared_ptr<const Feature>>& immutable_features_m={});

    Output(types typ,const QJsonValue& val);
    Output(types typ):type_m(typ){};

    template<class from_type> static std::shared_ptr<Output> from_(from_type& val);
    template<class deriv, class... Types> static std::shared_ptr<Output> get(Types... args)
    {
        return std::shared_ptr<Output>(new deriv(args...));
    }

    virtual void serialize(QDataStream &out)const;
    virtual QJsonObject get_Json(void) const;
    virtual void set_id(const c_array& id);
    virtual c_array get_id(void)const{return c_array(32,0);};
    virtual void consume(void);
    quint64 min_deposit_of_output(const quint64 &wkey, const quint64 &wdata, const quint64 &v_byte_cost)const;


    std::shared_ptr<const Unlock_Condition> get_unlock_(const Unlock_Condition::types& typ)const
    {
        const auto found=std::find_if(unlock_conditions_.begin(),unlock_conditions_.end(),
                                      [typ](const auto& it){return (it->type()==typ);});
        return (found==unlock_conditions_.end())?nullptr:*found;
    }

    std::shared_ptr<const Feature> get_feature_(const Feature::types& typ)const
    {
        const auto found=std::find_if(features_.begin(),features_.end(),
                                      [typ](const auto& it){return (it->type()==typ);});
        return (found==features_.end())?nullptr:*found;
    }
    std::shared_ptr<const Feature> get_immutable_feature_(const Feature::types& typ)const
    {
        const auto found=std::find_if(immutable_features_.begin(),immutable_features_.end(),
                                      [typ](const auto& it){return (it->type()==typ);});
        return (found==immutable_features_.end())?nullptr:*found;
    }


    quint64 amount_;
    std::vector<std::shared_ptr<const Unlock_Condition>> unlock_conditions_;
    std::vector<std::shared_ptr<const Feature>> features_;
    std::vector<std::shared_ptr<const Feature>> immutable_features_;
    std::vector<std::shared_ptr<const Native_Token>> native_tokens_;
    types type(void)const{return type_m;}
    const static QHash<types,QString > typesstr;
private:
    const types type_m;


};

class Basic_Output :public Output
{
public:
    Basic_Output(quint64 amount_m, const std::vector<std::shared_ptr<const Unlock_Condition> > &unlock_conditions_m,
                 const std::vector<std::shared_ptr<const Feature> > &features_m={},
                 const std::vector<std::shared_ptr<const Native_Token> > &native_tokens_m={});
    Basic_Output(const QJsonValue& val);
    Basic_Output(QDataStream &in);
    void serialize(QDataStream &out)const;
    QJsonObject get_Json(void) const;


};
class NFT_Output :public Output
{
public:
    NFT_Output(quint64 amount_m, const std::vector<std::shared_ptr<const Unlock_Condition> > &unlock_conditions_m,
               const std::vector<std::shared_ptr<const Feature> > &features_m={},
               const std::vector<std::shared_ptr<const Native_Token> > &native_tokens_m={},
               const std::vector<std::shared_ptr<const Feature> > &immutable_features_m={});
    NFT_Output(const QJsonValue& val);
    NFT_Output(QDataStream &in);
    void serialize(QDataStream &out)const;

    QJsonObject get_Json(void) const;
    void set_id(const c_array& id){nft_id_=id;};
    c_array get_id(void)const{return nft_id_;}

private:
    NFT_ID nft_id_;


};

class Foundry_Output :public Output
{
public:
    Foundry_Output(const quint64& amount_m, const std::vector<std::shared_ptr<const Unlock_Condition>> & unlock_conditions_m,
                   std::shared_ptr<Token_Scheme>& token_scheme_m, const quint32& serial_number_m,
               const std::vector<std::shared_ptr<const Feature>>& features_m,
               const std::vector<std::shared_ptr<const Native_Token>>& native_tokens_m,
               std::vector<std::shared_ptr<const Feature>> immutable_features_m={});
    Foundry_Output(const QJsonValue& val);
    Foundry_Output(QDataStream &in);
    void serialize(QDataStream &out)const;
    c_array get_id(void)const{
        c_array var;
        var=unlock_conditions_.front()->address()->addr();
        var.append(serial_number_);
        var.append(token_scheme_->type());
        return var;
    }
    void consume(void);
    QJsonObject get_Json(void) const;
    std::shared_ptr<Token_Scheme> token_scheme_;
    quint32 serial_number_;
private:


};

class Alias_Output :public Output
{
public:
    Alias_Output(const quint64& amount_m, const std::vector<std::shared_ptr<const Unlock_Condition>> & unlock_conditions_m,
                    const quint32& state_index_m=0, const quint32& foundry_counter_m=0,
                 const fl_array<quint16> &state_metadata_m="",
                 const std::vector<std::shared_ptr<const Feature>>& features_m={},
                 const std::vector<std::shared_ptr<const Native_Token>>& native_tokens_m={},
               const std::vector<std::shared_ptr<const Feature>>& immutable_features_m={});
    Alias_Output(const QJsonValue& val);
    Alias_Output(QDataStream &in);
    void serialize(QDataStream &out)const;

    QJsonObject get_Json(void) const;
    void set_id(const c_array& id){alias_id_=id;};
    c_array get_id(void)const{return alias_id_;}
    quint32 state_index_,foundry_counter_;
    fl_array<quint16> state_metadata_;
private:
    Alias_ID alias_id_;


};

};

};
