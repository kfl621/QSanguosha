#ifndef PLAYER_H
#define PLAYER_H

#include "general.h"
#include "card.h"

#include <QObject>
#include <QTcpSocket>
#include <QStack>

class EquipCard;
class Weapon;
class Armor;
class Horse;
class DelayedTrick;
class DistanceSkill;
class TriggerSkill;

class Player : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString screenname READ screenName WRITE setScreenName)
    Q_PROPERTY(int hp READ getHp WRITE setHp)
    Q_PROPERTY(int maxhp READ getMaxHP WRITE setMaxHP)
    Q_PROPERTY(QString kingdom READ getKingdom WRITE setKingdom)
    Q_PROPERTY(int xueyi READ getXueyi WRITE setXueyi)
    Q_PROPERTY(bool wounded READ isWounded STORED false)    
    Q_PROPERTY(QString role READ getRole WRITE setRole)
    Q_PROPERTY(QString general READ getGeneralName WRITE setGeneralName)
    Q_PROPERTY(QString general2 READ getGeneral2Name WRITE setGeneral2Name)
    Q_PROPERTY(QString state READ getState WRITE setState)
    Q_PROPERTY(int handcard_num READ getHandcardNum)
    Q_PROPERTY(int seat READ getSeat WRITE setSeat)
    Q_PROPERTY(QString phase READ getPhaseString WRITE setPhaseString)
    Q_PROPERTY(bool faceup READ faceUp WRITE setFaceUp)
    Q_PROPERTY(bool alive READ isAlive WRITE setAlive)
    Q_PROPERTY(QString flags READ getFlags WRITE setFlags)
    Q_PROPERTY(bool chained READ isChained WRITE setChained)
    Q_PROPERTY(bool owner READ isOwner WRITE setOwner)
    Q_PROPERTY(int atk READ getAttackRange WRITE setAttackRange)

    Q_PROPERTY(bool kongcheng READ isKongcheng)
    Q_PROPERTY(bool nude READ isNude)
    Q_PROPERTY(bool all_nude READ isAllNude)

    Q_ENUMS(Phase)
    Q_ENUMS(Place)
    Q_ENUMS(Role)

public:
    enum Phase {Start, Judge, Draw, Play, Discard, Finish, NotActive};
    enum Place {Hand, Equip, Judging, Special, DiscardedPile, DrawPile};
    enum Role {Lord, Loyalist, Rebel, Renegade};

    explicit Player(QObject *parent);

    void setScreenName(const QString &screen_name);
    QString screenName() const;

    // property setters/getters
    int getHp() const;
    void setHp(int hp);    
    int getMaxHP() const;
    void setMaxHP(int max_hp);    
    int getLostHp() const;
    bool isWounded() const;

    bool isOwner() const;
    void setOwner(bool owner);

    int getMaxCards() const;    
    int getXueyi() const;
    void setXueyi(int xueyi);

    QString getKingdom() const;
    void setKingdom(const QString &kingdom);
    QString getKingdomIcon() const;
    QString getKingdomFrame() const;

    void setRole(const QString &role);
    QString getRole() const;    
    Role getRoleEnum() const;

    void setGeneral(const General *general);
    void setGeneralName(const QString &general_name);
    QString getGeneralName() const;    

    void setGeneral2Name(const QString &general_name);
    QString getGeneral2Name() const;
    const General *getGeneral2() const;

    void setState(const QString &state);
    QString getState() const;

    int getSeat() const;
    void setSeat(int seat);  
    QString getPhaseString() const;
    void setPhaseString(const QString &phase_str);
    Phase getPhase() const;
    void setPhase(Phase phase);

    void setAttackRange(int attack_range);
    int getAttackRange() const;
    bool inMyAttackRange(const Player *other) const;

    bool isAlive() const;
    bool isDead() const;
    void setAlive(bool alive);

    QString getFlags() const;
    virtual void setFlags(const QString &flag);
    bool hasFlag(const QString &flag) const;
    void clearFlags();

    bool faceUp() const;
    void setFaceUp(bool face_up);

    virtual int aliveCount() const = 0;
    void setFixedDistance(const Player *player, int distance);
    int distanceTo(const Player *other) const;
    const General *getAvatarGeneral() const;
    const General *getGeneral() const;

    void acquireSkill(const QString &skill_name);
    void loseSkill(const QString &skill_name);
    void loseAllSkills();
    bool hasSkill(const QString &skill_name) const;

    void setEquip(const EquipCard *card);
    void removeEquip(const EquipCard *equip);
    bool hasEquip(const Card *card) const;

    QStack<const Card *> getJudgingArea() const;
    void addDelayedTrick(const Card *trick);
    void removeDelayedTrick(const Card *trick);
    QStack<const DelayedTrick *> delayedTricks() const;
    bool containsTrick(const QString &trick_name) const;
    const DelayedTrick *topDelayedTrick() const;

    virtual int getHandcardNum() const = 0;
    virtual void removeCard(const Card *card, Place place) = 0;
    virtual void addCard(const Card *card, Place place) = 0;

    const Weapon *getWeapon() const;
    const Armor *getArmor() const;
    const Horse *getDefensiveHorse() const;
    const Horse *getOffensiveHorse() const;
    QList<const Card *> getEquips() const;
    const EquipCard *getEquip(int index) const;

    bool hasWeapon(const QString &weapon_name) const;
    bool hasArmorEffect(const QString &armor_name) const;

    bool isKongcheng() const;
    bool isNude() const;
    bool isAllNude() const;

    void addMark(const QString &mark);
    void removeMark(const QString &mark);
    virtual void setMark(const QString &mark, int value);
    int getMark(const QString &mark) const;

    void setChained(bool chained);
    bool isChained() const;

    bool canSlash(const Player *other, bool distance_limit = true) const;
    int getCardCount(bool include_equip) const;

    QList<int> &getPile(const QString &pile_name);

    void addHistory(const Card *card);
    void clearHistory();
    bool hasUsed(const QString &card_class);
    int usedTimes(const QString &card_class);

    QList<const TriggerSkill *> getTriggerSkills() const;
    QList<const Skill *> getVisibleSkills() const;

    QVariantMap tag;

protected:
    QMap<QString, int> marks;
    QMap<QString, QList<int> > piles;

private:    
    QString screen_name;
    bool owner;
    const General *general, *general2;
    int hp, max_hp, xueyi;
    QString kingdom;
    QString role;
    QString state;
    int seat;
    bool alive;
    QSet<QString> flags;
    QSet<QString> acquired_skills;

    int attack_range;

    Phase phase;
    const Weapon *weapon;
    const Armor *armor;
    const Horse *defensive_horse, *offensive_horse;
    bool face_up;
    bool chained;
    QStack<const Card *> judging_area;
    QStack<const DelayedTrick *> delayed_tricks;
    QHash<const Player *, int> fixed_distance;

    QHash<QString, int> history;

signals:
    void general_changed();
    void general2_changed();
    void role_changed(const QString &new_role);
    void state_changed();
    void kingdom_changed();
    void phase_changed();
    void owner_changed(bool owner);
};

#endif // PLAYER_H
