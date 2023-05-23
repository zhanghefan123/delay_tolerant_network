//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/projects/dtn_network/dtn_packets/EpidemicHeader.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "EpidemicHeader_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

Register_Class(EpidemicHeader)

EpidemicHeader::EpidemicHeader() : ::inet::FieldsChunk()
{
}

EpidemicHeader::EpidemicHeader(const EpidemicHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

EpidemicHeader::~EpidemicHeader()
{
    delete [] this->msgIds;
}

EpidemicHeader& EpidemicHeader::operator=(const EpidemicHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void EpidemicHeader::copy(const EpidemicHeader& other)
{
    this->type = other.type;
    this->uuid = other.uuid;
    this->neighborAck = other.neighborAck;
    this->msgIdLength = other.msgIdLength;
    delete [] this->msgIds;
    this->msgIds = (other.msgIds_arraysize==0) ? nullptr : new ::omnetpp::opp_string[other.msgIds_arraysize];
    msgIds_arraysize = other.msgIds_arraysize;
    for (size_t i = 0; i < msgIds_arraysize; i++) {
        this->msgIds[i] = other.msgIds[i];
    }
    this->destAddr = other.destAddr;
}

void EpidemicHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->uuid);
    doParsimPacking(b,this->neighborAck);
    doParsimPacking(b,this->msgIdLength);
    b->pack(msgIds_arraysize);
    doParsimArrayPacking(b,this->msgIds,msgIds_arraysize);
    doParsimPacking(b,this->destAddr);
}

void EpidemicHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->uuid);
    doParsimUnpacking(b,this->neighborAck);
    doParsimUnpacking(b,this->msgIdLength);
    delete [] this->msgIds;
    b->unpack(msgIds_arraysize);
    if (msgIds_arraysize == 0) {
        this->msgIds = nullptr;
    } else {
        this->msgIds = new ::omnetpp::opp_string[msgIds_arraysize];
        doParsimArrayUnpacking(b,this->msgIds,msgIds_arraysize);
    }
    doParsimUnpacking(b,this->destAddr);
}

short EpidemicHeader::getType() const
{
    return this->type;
}

void EpidemicHeader::setType(short type)
{
    handleChange();
    this->type = type;
}

const char * EpidemicHeader::getUuid() const
{
    return this->uuid.c_str();
}

void EpidemicHeader::setUuid(const char * uuid)
{
    handleChange();
    this->uuid = uuid;
}

bool EpidemicHeader::getNeighborAck() const
{
    return this->neighborAck;
}

void EpidemicHeader::setNeighborAck(bool neighborAck)
{
    handleChange();
    this->neighborAck = neighborAck;
}

int EpidemicHeader::getMsgIdLength() const
{
    return this->msgIdLength;
}

void EpidemicHeader::setMsgIdLength(int msgIdLength)
{
    handleChange();
    this->msgIdLength = msgIdLength;
}

size_t EpidemicHeader::getMsgIdsArraySize() const
{
    return msgIds_arraysize;
}

const char * EpidemicHeader::getMsgIds(size_t k) const
{
    if (k >= msgIds_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)msgIds_arraysize, (unsigned long)k);
    return this->msgIds[k].c_str();
}

void EpidemicHeader::setMsgIdsArraySize(size_t newSize)
{
    handleChange();
    ::omnetpp::opp_string *msgIds2 = (newSize==0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t minSize = msgIds_arraysize < newSize ? msgIds_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        msgIds2[i] = this->msgIds[i];
    delete [] this->msgIds;
    this->msgIds = msgIds2;
    msgIds_arraysize = newSize;
}

void EpidemicHeader::setMsgIds(size_t k, const char * msgIds)
{
    if (k >= msgIds_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)msgIds_arraysize, (unsigned long)k);
    handleChange();
    this->msgIds[k] = msgIds;
}

void EpidemicHeader::insertMsgIds(size_t k, const char * msgIds)
{
    if (k > msgIds_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)msgIds_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = msgIds_arraysize + 1;
    ::omnetpp::opp_string *msgIds2 = new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        msgIds2[i] = this->msgIds[i];
    msgIds2[k] = msgIds;
    for (i = k + 1; i < newSize; i++)
        msgIds2[i] = this->msgIds[i-1];
    delete [] this->msgIds;
    this->msgIds = msgIds2;
    msgIds_arraysize = newSize;
}

void EpidemicHeader::appendMsgIds(const char * msgIds)
{
    insertMsgIds(msgIds_arraysize, msgIds);
}

void EpidemicHeader::eraseMsgIds(size_t k)
{
    if (k >= msgIds_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)msgIds_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = msgIds_arraysize - 1;
    ::omnetpp::opp_string *msgIds2 = (newSize == 0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        msgIds2[i] = this->msgIds[i];
    for (i = k; i < newSize; i++)
        msgIds2[i] = this->msgIds[i+1];
    delete [] this->msgIds;
    this->msgIds = msgIds2;
    msgIds_arraysize = newSize;
}

const Ipv4Address& EpidemicHeader::getDestAddr() const
{
    return this->destAddr;
}

void EpidemicHeader::setDestAddr(const Ipv4Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

class EpidemicHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_uuid,
        FIELD_neighborAck,
        FIELD_msgIdLength,
        FIELD_msgIds,
        FIELD_destAddr,
    };
  public:
    EpidemicHeaderDescriptor();
    virtual ~EpidemicHeaderDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(EpidemicHeaderDescriptor)

EpidemicHeaderDescriptor::EpidemicHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::EpidemicHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

EpidemicHeaderDescriptor::~EpidemicHeaderDescriptor()
{
    delete[] propertyNames;
}

bool EpidemicHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EpidemicHeader *>(obj)!=nullptr;
}

const char **EpidemicHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EpidemicHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EpidemicHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int EpidemicHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_uuid
        FD_ISEDITABLE,    // FIELD_neighborAck
        FD_ISEDITABLE,    // FIELD_msgIdLength
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_msgIds
        0,    // FIELD_destAddr
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *EpidemicHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "uuid",
        "neighborAck",
        "msgIdLength",
        "msgIds",
        "destAddr",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int EpidemicHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "uuid") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "neighborAck") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "msgIdLength") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "msgIds") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *EpidemicHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_type
        "string",    // FIELD_uuid
        "bool",    // FIELD_neighborAck
        "int",    // FIELD_msgIdLength
        "string",    // FIELD_msgIds
        "inet::Ipv4Address",    // FIELD_destAddr
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **EpidemicHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EpidemicHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EpidemicHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EpidemicHeader *pp = omnetpp::fromAnyPtr<EpidemicHeader>(object); (void)pp;
    switch (field) {
        case FIELD_msgIds: return pp->getMsgIdsArraySize();
        default: return 0;
    }
}

void EpidemicHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EpidemicHeader *pp = omnetpp::fromAnyPtr<EpidemicHeader>(object); (void)pp;
    switch (field) {
        case FIELD_msgIds: pp->setMsgIdsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EpidemicHeader'", field);
    }
}

const char *EpidemicHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EpidemicHeader *pp = omnetpp::fromAnyPtr<EpidemicHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EpidemicHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EpidemicHeader *pp = omnetpp::fromAnyPtr<EpidemicHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: return long2string(pp->getType());
        case FIELD_uuid: return oppstring2string(pp->getUuid());
        case FIELD_neighborAck: return bool2string(pp->getNeighborAck());
        case FIELD_msgIdLength: return long2string(pp->getMsgIdLength());
        case FIELD_msgIds: return oppstring2string(pp->getMsgIds(i));
        case FIELD_destAddr: return pp->getDestAddr().str();
        default: return "";
    }
}

void EpidemicHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EpidemicHeader *pp = omnetpp::fromAnyPtr<EpidemicHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(string2long(value)); break;
        case FIELD_uuid: pp->setUuid((value)); break;
        case FIELD_neighborAck: pp->setNeighborAck(string2bool(value)); break;
        case FIELD_msgIdLength: pp->setMsgIdLength(string2long(value)); break;
        case FIELD_msgIds: pp->setMsgIds(i,(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EpidemicHeader'", field);
    }
}

omnetpp::cValue EpidemicHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EpidemicHeader *pp = omnetpp::fromAnyPtr<EpidemicHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: return pp->getType();
        case FIELD_uuid: return pp->getUuid();
        case FIELD_neighborAck: return pp->getNeighborAck();
        case FIELD_msgIdLength: return pp->getMsgIdLength();
        case FIELD_msgIds: return pp->getMsgIds(i);
        case FIELD_destAddr: return pp->getDestAddr().str();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EpidemicHeader' as cValue -- field index out of range?", field);
    }
}

void EpidemicHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EpidemicHeader *pp = omnetpp::fromAnyPtr<EpidemicHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_uuid: pp->setUuid(value.stringValue()); break;
        case FIELD_neighborAck: pp->setNeighborAck(value.boolValue()); break;
        case FIELD_msgIdLength: pp->setMsgIdLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_msgIds: pp->setMsgIds(i,value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EpidemicHeader'", field);
    }
}

const char *EpidemicHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr EpidemicHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EpidemicHeader *pp = omnetpp::fromAnyPtr<EpidemicHeader>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EpidemicHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EpidemicHeader *pp = omnetpp::fromAnyPtr<EpidemicHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EpidemicHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

