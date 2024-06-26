//
// Generated file, do not edit! Created by opp_msgtool 6.0 from Remote_Sensing_System_Message.msg.
//

#ifndef __REMOTESENSINGSYSTEM_REMOTE_SENSING_SYSTEM_MESSAGE_M_H
#define __REMOTESENSINGSYSTEM_REMOTE_SENSING_SYSTEM_MESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif


namespace remotesensingsystem {

class Remote_Sensing_System_Message;

}  // namespace remotesensingsystem

// cplusplus {{
    
// }}


namespace remotesensingsystem {

/**
 * Class generated from <tt>Remote_Sensing_System_Message.msg:8</tt> by opp_msgtool.
 * <pre>
 * message Remote_Sensing_System_Message extends cMessage
 * {
 *     double x;
 *     double y;
 *     double D;
 * }
 * </pre>
 */
class Remote_Sensing_System_Message : public ::omnetpp::cMessage
{
  protected:
    double x = 0;
    double y = 0;
    double D = 0;

  private:
    void copy(const Remote_Sensing_System_Message& other);

  protected:
    bool operator==(const Remote_Sensing_System_Message&) = delete;

  public:
    Remote_Sensing_System_Message(const char *name=nullptr, short kind=0);
    Remote_Sensing_System_Message(const Remote_Sensing_System_Message& other);
    virtual ~Remote_Sensing_System_Message();
    Remote_Sensing_System_Message& operator=(const Remote_Sensing_System_Message& other);
    virtual Remote_Sensing_System_Message *dup() const override {return new Remote_Sensing_System_Message(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual double getX() const;
    virtual void setX(double x);

    virtual double getY() const;
    virtual void setY(double y);

    virtual double getD() const;
    virtual void setD(double D);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Remote_Sensing_System_Message& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Remote_Sensing_System_Message& obj) {obj.parsimUnpack(b);}


}  // namespace remotesensingsystem


namespace omnetpp {

template<> inline remotesensingsystem::Remote_Sensing_System_Message *fromAnyPtr(any_ptr ptr) { return check_and_cast<remotesensingsystem::Remote_Sensing_System_Message*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __REMOTESENSINGSYSTEM_REMOTE_SENSING_SYSTEM_MESSAGE_M_H

