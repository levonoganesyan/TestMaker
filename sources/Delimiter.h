#ifndef DELIMITER___
#define DELIMITER___

#include"Test.h"
#include"Range.h"

/// Class Delimiter
/// Class that describes Delimiter, like '\n' or "|||"
class Delimiter : public Test
{
protected:
	std::string delimiter_;
public:
	/// Delimiter constructor
	/// \param _delimiter - delimiter
	Delimiter(char _delimiter);
	/// Delimiter constructor
	/// \param _delimiter - delimiter
	Delimiter(const std::string& _delimiter);
	std::string Get();
	virtual Delimiter* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual Delimiter* Clone() const;
	virtual ~Delimiter();
};

#endif