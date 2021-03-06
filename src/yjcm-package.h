#ifndef YJCMPACKAGE_H
#define YJCMPACKAGE_H

#include "package.h"
#include "card.h"

class YJCMPackage: public Package{
    Q_OBJECT

public:
    YJCMPackage();
};

class JujianCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE JujianCard();

    virtual void onEffect(const CardEffectStruct &effect) const;
};

class MingceCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE MingceCard();

    virtual void onEffect(const CardEffectStruct &effect) const;
};

class GanluCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE GanluCard();
    void swapEquip(ServerPlayer *first, ServerPlayer *second, int index) const;

    virtual bool targetsFeasible(const QList<const ClientPlayer *> &targets) const;
    virtual bool targetFilter(const QList<const ClientPlayer *> &targets, const ClientPlayer *to_select) const;
    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class XianzhenSlashCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE XianzhenSlashCard();

    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
};

class XianzhenCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE XianzhenCard();

    virtual bool targetFilter(const QList<const ClientPlayer *> &targets, const ClientPlayer *to_select) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class XuanhuoCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE XuanhuoCard();

    virtual void onEffect(const CardEffectStruct &effect) const;
};

class XinzhanCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE XinzhanCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

#endif // YJCMPACKAGE_H
