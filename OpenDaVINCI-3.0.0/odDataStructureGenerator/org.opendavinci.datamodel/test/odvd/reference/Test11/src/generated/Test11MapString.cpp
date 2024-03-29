/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"


#include "test11/generated/Test11MapString.h"

	using namespace std;
	using namespace odcore::base;


	Test11MapString::Test11MapString() :
	    SerializableData(), Visitable()
		, m_mapOfMyStringBoolMap()
		, m_mapOfMyStringCharMap()
		, m_mapOfMyStringInt32Map()
		, m_mapOfMyStringUint32Map()
		, m_mapOfMyStringFloatMap()
		, m_mapOfMyStringDoubleMap()
		, m_mapOfMyStringStringMap()
	{
	}

	Test11MapString::Test11MapString(
		const map<std::string, bool> &val0, 
		const map<std::string, char> &val1, 
		const map<std::string, int32_t> &val2, 
		const map<std::string, uint32_t> &val3, 
		const map<std::string, float> &val4, 
		const map<std::string, double> &val5, 
		const map<std::string, std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_mapOfMyStringBoolMap(val0)
		, m_mapOfMyStringCharMap(val1)
		, m_mapOfMyStringInt32Map(val2)
		, m_mapOfMyStringUint32Map(val3)
		, m_mapOfMyStringFloatMap(val4)
		, m_mapOfMyStringDoubleMap(val5)
		, m_mapOfMyStringStringMap(val6)
	{
	}

	Test11MapString::Test11MapString(const Test11MapString &obj) :
	    SerializableData(), Visitable()
		, m_mapOfMyStringBoolMap(obj.m_mapOfMyStringBoolMap)
		, m_mapOfMyStringCharMap(obj.m_mapOfMyStringCharMap)
		, m_mapOfMyStringInt32Map(obj.m_mapOfMyStringInt32Map)
		, m_mapOfMyStringUint32Map(obj.m_mapOfMyStringUint32Map)
		, m_mapOfMyStringFloatMap(obj.m_mapOfMyStringFloatMap)
		, m_mapOfMyStringDoubleMap(obj.m_mapOfMyStringDoubleMap)
		, m_mapOfMyStringStringMap(obj.m_mapOfMyStringStringMap)
	{
	}
	
	Test11MapString::~Test11MapString() {
	}

	Test11MapString& Test11MapString::operator=(const Test11MapString &obj) {
		m_mapOfMyStringBoolMap = obj.m_mapOfMyStringBoolMap;
		m_mapOfMyStringCharMap = obj.m_mapOfMyStringCharMap;
		m_mapOfMyStringInt32Map = obj.m_mapOfMyStringInt32Map;
		m_mapOfMyStringUint32Map = obj.m_mapOfMyStringUint32Map;
		m_mapOfMyStringFloatMap = obj.m_mapOfMyStringFloatMap;
		m_mapOfMyStringDoubleMap = obj.m_mapOfMyStringDoubleMap;
		m_mapOfMyStringStringMap = obj.m_mapOfMyStringStringMap;
		return (*this);
	}

	int32_t Test11MapString::ID() {
		return 19;
	}

	const string Test11MapString::ShortName() {
		return "Test11MapString";
	}

	const string Test11MapString::LongName() {
		return "Test11MapString";
	}

	int32_t Test11MapString::getID() const {
		return Test11MapString::ID();
	}

	const string Test11MapString::getShortName() const {
		return Test11MapString::ShortName();
	}

	const string Test11MapString::getLongName() const {
		return Test11MapString::LongName();
	}

	std::map<std::string, bool> Test11MapString::getMapOfMyStringBoolMap() const {
		return m_mapOfMyStringBoolMap;
	}
	
	void Test11MapString::setMapOfMyStringBoolMap(const std::map<std::string, bool> &val) {
		m_mapOfMyStringBoolMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringBoolMap() {
		m_mapOfMyStringBoolMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringBoolMap() const {
		return m_mapOfMyStringBoolMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringBoolMap() const {
		return m_mapOfMyStringBoolMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringBoolMap(const std::string &key, const bool &val) {
		m_mapOfMyStringBoolMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringBoolMap(const std::string &key) const {
		return (m_mapOfMyStringBoolMap.count(key) > 0);
	}
	
	bool Test11MapString::getValueForKey_MapOfMyStringBoolMap(const std::string &key) {
		return m_mapOfMyStringBoolMap[key];
	}
	
	std::pair<std::map<std::string, bool>::iterator, std::map<std::string, bool>::iterator> Test11MapString::iteratorPair_MapOfMyStringBoolMap() {
		return std::make_pair(m_mapOfMyStringBoolMap.begin(), m_mapOfMyStringBoolMap.end());
	}
	std::map<std::string, char> Test11MapString::getMapOfMyStringCharMap() const {
		return m_mapOfMyStringCharMap;
	}
	
	void Test11MapString::setMapOfMyStringCharMap(const std::map<std::string, char> &val) {
		m_mapOfMyStringCharMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringCharMap() {
		m_mapOfMyStringCharMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringCharMap() const {
		return m_mapOfMyStringCharMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringCharMap() const {
		return m_mapOfMyStringCharMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringCharMap(const std::string &key, const char &val) {
		m_mapOfMyStringCharMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringCharMap(const std::string &key) const {
		return (m_mapOfMyStringCharMap.count(key) > 0);
	}
	
	char Test11MapString::getValueForKey_MapOfMyStringCharMap(const std::string &key) {
		return m_mapOfMyStringCharMap[key];
	}
	
	std::pair<std::map<std::string, char>::iterator, std::map<std::string, char>::iterator> Test11MapString::iteratorPair_MapOfMyStringCharMap() {
		return std::make_pair(m_mapOfMyStringCharMap.begin(), m_mapOfMyStringCharMap.end());
	}
	std::map<std::string, int32_t> Test11MapString::getMapOfMyStringInt32Map() const {
		return m_mapOfMyStringInt32Map;
	}
	
	void Test11MapString::setMapOfMyStringInt32Map(const std::map<std::string, int32_t> &val) {
		m_mapOfMyStringInt32Map = val;
	}
	
	void Test11MapString::clear_MapOfMyStringInt32Map() {
		m_mapOfMyStringInt32Map.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringInt32Map() const {
		return m_mapOfMyStringInt32Map.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringInt32Map() const {
		return m_mapOfMyStringInt32Map.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringInt32Map(const std::string &key, const int32_t &val) {
		m_mapOfMyStringInt32Map[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringInt32Map(const std::string &key) const {
		return (m_mapOfMyStringInt32Map.count(key) > 0);
	}
	
	int32_t Test11MapString::getValueForKey_MapOfMyStringInt32Map(const std::string &key) {
		return m_mapOfMyStringInt32Map[key];
	}
	
	std::pair<std::map<std::string, int32_t>::iterator, std::map<std::string, int32_t>::iterator> Test11MapString::iteratorPair_MapOfMyStringInt32Map() {
		return std::make_pair(m_mapOfMyStringInt32Map.begin(), m_mapOfMyStringInt32Map.end());
	}
	std::map<std::string, uint32_t> Test11MapString::getMapOfMyStringUint32Map() const {
		return m_mapOfMyStringUint32Map;
	}
	
	void Test11MapString::setMapOfMyStringUint32Map(const std::map<std::string, uint32_t> &val) {
		m_mapOfMyStringUint32Map = val;
	}
	
	void Test11MapString::clear_MapOfMyStringUint32Map() {
		m_mapOfMyStringUint32Map.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringUint32Map() const {
		return m_mapOfMyStringUint32Map.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringUint32Map() const {
		return m_mapOfMyStringUint32Map.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringUint32Map(const std::string &key, const uint32_t &val) {
		m_mapOfMyStringUint32Map[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringUint32Map(const std::string &key) const {
		return (m_mapOfMyStringUint32Map.count(key) > 0);
	}
	
	uint32_t Test11MapString::getValueForKey_MapOfMyStringUint32Map(const std::string &key) {
		return m_mapOfMyStringUint32Map[key];
	}
	
	std::pair<std::map<std::string, uint32_t>::iterator, std::map<std::string, uint32_t>::iterator> Test11MapString::iteratorPair_MapOfMyStringUint32Map() {
		return std::make_pair(m_mapOfMyStringUint32Map.begin(), m_mapOfMyStringUint32Map.end());
	}
	std::map<std::string, float> Test11MapString::getMapOfMyStringFloatMap() const {
		return m_mapOfMyStringFloatMap;
	}
	
	void Test11MapString::setMapOfMyStringFloatMap(const std::map<std::string, float> &val) {
		m_mapOfMyStringFloatMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringFloatMap() {
		m_mapOfMyStringFloatMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringFloatMap() const {
		return m_mapOfMyStringFloatMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringFloatMap() const {
		return m_mapOfMyStringFloatMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringFloatMap(const std::string &key, const float &val) {
		m_mapOfMyStringFloatMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringFloatMap(const std::string &key) const {
		return (m_mapOfMyStringFloatMap.count(key) > 0);
	}
	
	float Test11MapString::getValueForKey_MapOfMyStringFloatMap(const std::string &key) {
		return m_mapOfMyStringFloatMap[key];
	}
	
	std::pair<std::map<std::string, float>::iterator, std::map<std::string, float>::iterator> Test11MapString::iteratorPair_MapOfMyStringFloatMap() {
		return std::make_pair(m_mapOfMyStringFloatMap.begin(), m_mapOfMyStringFloatMap.end());
	}
	std::map<std::string, double> Test11MapString::getMapOfMyStringDoubleMap() const {
		return m_mapOfMyStringDoubleMap;
	}
	
	void Test11MapString::setMapOfMyStringDoubleMap(const std::map<std::string, double> &val) {
		m_mapOfMyStringDoubleMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringDoubleMap() {
		m_mapOfMyStringDoubleMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringDoubleMap() const {
		return m_mapOfMyStringDoubleMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringDoubleMap() const {
		return m_mapOfMyStringDoubleMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringDoubleMap(const std::string &key, const double &val) {
		m_mapOfMyStringDoubleMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringDoubleMap(const std::string &key) const {
		return (m_mapOfMyStringDoubleMap.count(key) > 0);
	}
	
	double Test11MapString::getValueForKey_MapOfMyStringDoubleMap(const std::string &key) {
		return m_mapOfMyStringDoubleMap[key];
	}
	
	std::pair<std::map<std::string, double>::iterator, std::map<std::string, double>::iterator> Test11MapString::iteratorPair_MapOfMyStringDoubleMap() {
		return std::make_pair(m_mapOfMyStringDoubleMap.begin(), m_mapOfMyStringDoubleMap.end());
	}
	std::map<std::string, std::string> Test11MapString::getMapOfMyStringStringMap() const {
		return m_mapOfMyStringStringMap;
	}
	
	void Test11MapString::setMapOfMyStringStringMap(const std::map<std::string, std::string> &val) {
		m_mapOfMyStringStringMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringStringMap() {
		m_mapOfMyStringStringMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringStringMap() const {
		return m_mapOfMyStringStringMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringStringMap() const {
		return m_mapOfMyStringStringMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringStringMap(const std::string &key, const std::string &val) {
		m_mapOfMyStringStringMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringStringMap(const std::string &key) const {
		return (m_mapOfMyStringStringMap.count(key) > 0);
	}
	
	std::string Test11MapString::getValueForKey_MapOfMyStringStringMap(const std::string &key) {
		return m_mapOfMyStringStringMap[key];
	}
	
	std::pair<std::map<std::string, std::string>::iterator, std::map<std::string, std::string>::iterator> Test11MapString::iteratorPair_MapOfMyStringStringMap() {
		return std::make_pair(m_mapOfMyStringStringMap.begin(), m_mapOfMyStringStringMap.end());
	}

	void Test11MapString::accept(odcore::base::Visitor &v) {
		(void)v; // Avoid unused parameter warning.
	}

	const string Test11MapString::toString() const {
		stringstream s;


		s << "Number of elements in map of MyStringBoolMap: " << getSize_MapOfMyStringBoolMap() << " ";
		s << "Number of elements in map of MyStringCharMap: " << getSize_MapOfMyStringCharMap() << " ";
		s << "Number of elements in map of MyStringInt32Map: " << getSize_MapOfMyStringInt32Map() << " ";
		s << "Number of elements in map of MyStringUint32Map: " << getSize_MapOfMyStringUint32Map() << " ";
		s << "Number of elements in map of MyStringFloatMap: " << getSize_MapOfMyStringFloatMap() << " ";
		s << "Number of elements in map of MyStringDoubleMap: " << getSize_MapOfMyStringDoubleMap() << " ";
		s << "Number of elements in map of MyStringStringMap: " << getSize_MapOfMyStringStringMap() << " ";

		return s.str();
	}

	ostream& Test11MapString::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		{
			// Write number of elements in m_mapOfMyStringBoolMap.
			const uint32_t numberOfMyStringBoolMap = static_cast<uint32_t>(m_mapOfMyStringBoolMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyStringBoolMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyStringBoolMap;
			std::map<std::string, bool>::const_iterator it = m_mapOfMyStringBoolMap.begin();
			while (it != m_mapOfMyStringBoolMap.end()) {
			    sstrOfMyStringBoolMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyStringBoolMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyStringBoolMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyStringCharMap.
			const uint32_t numberOfMyStringCharMap = static_cast<uint32_t>(m_mapOfMyStringCharMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyStringCharMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyStringCharMap;
			std::map<std::string, char>::const_iterator it = m_mapOfMyStringCharMap.begin();
			while (it != m_mapOfMyStringCharMap.end()) {
			    sstrOfMyStringCharMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyStringCharMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyStringCharMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyStringInt32Map.
			const uint32_t numberOfMyStringInt32Map = static_cast<uint32_t>(m_mapOfMyStringInt32Map.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyStringInt32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyStringInt32Map;
			std::map<std::string, int32_t>::const_iterator it = m_mapOfMyStringInt32Map.begin();
			while (it != m_mapOfMyStringInt32Map.end()) {
			    sstrOfMyStringInt32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyStringInt32Map > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyStringInt32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyStringUint32Map.
			const uint32_t numberOfMyStringUint32Map = static_cast<uint32_t>(m_mapOfMyStringUint32Map.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyStringUint32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyStringUint32Map;
			std::map<std::string, uint32_t>::const_iterator it = m_mapOfMyStringUint32Map.begin();
			while (it != m_mapOfMyStringUint32Map.end()) {
			    sstrOfMyStringUint32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyStringUint32Map > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyStringUint32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyStringFloatMap.
			const uint32_t numberOfMyStringFloatMap = static_cast<uint32_t>(m_mapOfMyStringFloatMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyStringFloatMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyStringFloatMap;
			std::map<std::string, float>::const_iterator it = m_mapOfMyStringFloatMap.begin();
			while (it != m_mapOfMyStringFloatMap.end()) {
			    sstrOfMyStringFloatMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyStringFloatMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyStringFloatMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyStringDoubleMap.
			const uint32_t numberOfMyStringDoubleMap = static_cast<uint32_t>(m_mapOfMyStringDoubleMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyStringDoubleMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyStringDoubleMap;
			std::map<std::string, double>::const_iterator it = m_mapOfMyStringDoubleMap.begin();
			while (it != m_mapOfMyStringDoubleMap.end()) {
			    sstrOfMyStringDoubleMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyStringDoubleMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyStringDoubleMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyStringStringMap.
			const uint32_t numberOfMyStringStringMap = static_cast<uint32_t>(m_mapOfMyStringStringMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyStringStringMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyStringStringMap;
			std::map<std::string, std::string>::const_iterator it = m_mapOfMyStringStringMap.begin();
			while (it != m_mapOfMyStringStringMap.end()) {
			    sstrOfMyStringStringMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyStringStringMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyStringStringMap.str());
			}
		}
		return out;
	}

	istream& Test11MapString::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing map of MyStringBoolMap.
		m_mapOfMyStringBoolMap.clear();
		
		// Read number of elements in m_mapOfMyStringBoolMap.
		uint32_t numberOfMyStringBoolMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyStringBoolMap);
		
		if (numberOfMyStringBoolMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    std::string _key;
		        getline(sstrKey, _key);
		
			    stringstream sstrValue(value);
			    bool _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyStringBoolMap(_key, _value);
			}
		}
		// Clean up the existing map of MyStringCharMap.
		m_mapOfMyStringCharMap.clear();
		
		// Read number of elements in m_mapOfMyStringCharMap.
		uint32_t numberOfMyStringCharMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyStringCharMap);
		
		if (numberOfMyStringCharMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    std::string _key;
		        getline(sstrKey, _key);
		
			    stringstream sstrValue(value);
			    char _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyStringCharMap(_key, _value);
			}
		}
		// Clean up the existing map of MyStringInt32Map.
		m_mapOfMyStringInt32Map.clear();
		
		// Read number of elements in m_mapOfMyStringInt32Map.
		uint32_t numberOfMyStringInt32Map = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyStringInt32Map);
		
		if (numberOfMyStringInt32Map > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    std::string _key;
		        getline(sstrKey, _key);
		
			    stringstream sstrValue(value);
			    int32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyStringInt32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyStringUint32Map.
		m_mapOfMyStringUint32Map.clear();
		
		// Read number of elements in m_mapOfMyStringUint32Map.
		uint32_t numberOfMyStringUint32Map = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyStringUint32Map);
		
		if (numberOfMyStringUint32Map > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    std::string _key;
		        getline(sstrKey, _key);
		
			    stringstream sstrValue(value);
			    uint32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyStringUint32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyStringFloatMap.
		m_mapOfMyStringFloatMap.clear();
		
		// Read number of elements in m_mapOfMyStringFloatMap.
		uint32_t numberOfMyStringFloatMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyStringFloatMap);
		
		if (numberOfMyStringFloatMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    std::string _key;
		        getline(sstrKey, _key);
		
			    stringstream sstrValue(value);
			    float _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyStringFloatMap(_key, _value);
			}
		}
		// Clean up the existing map of MyStringDoubleMap.
		m_mapOfMyStringDoubleMap.clear();
		
		// Read number of elements in m_mapOfMyStringDoubleMap.
		uint32_t numberOfMyStringDoubleMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyStringDoubleMap);
		
		if (numberOfMyStringDoubleMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    std::string _key;
		        getline(sstrKey, _key);
		
			    stringstream sstrValue(value);
			    double _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyStringDoubleMap(_key, _value);
			}
		}
		// Clean up the existing map of MyStringStringMap.
		m_mapOfMyStringStringMap.clear();
		
		// Read number of elements in m_mapOfMyStringStringMap.
		uint32_t numberOfMyStringStringMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyStringStringMap);
		
		if (numberOfMyStringStringMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    std::string _key;
		        getline(sstrKey, _key);
		
			    stringstream sstrValue(value);
			    std::string _value;
		        getline(sstrValue, _value);
		
				// Store key/value pair.
				putTo_MapOfMyStringStringMap(_key, _value);
			}
		}
		return in;
	}
