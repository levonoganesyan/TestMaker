#ifndef GRAMMAR___
#define GRAMMAR___

#include "CompositeTest.h"

/// \class Grammar
/// Class that implements context-free grammar.
class Grammar : public CompositeTest
{
protected:
	/// \cond
	std::string grammar_, rules_;
	std::map<std::string, std::vector<std::string> > parsed_rules_;
	std::set<std::string> names_of_nonterm_;
	std::set<char> terms_;
	std::string start_nonterm_;
	std::string current_string_;
	virtual void NonTermsParsing(const std::string &);
	virtual void StartNonTermParsing(const std::string &);
	virtual void TermsParsing(const std::string &);
	virtual void RuleParsing(const std::string &);
	virtual void GrammarParsing();
	/// \endcond
public:
	/// grammar G = (N, Sigma, P, S)
	/// N = non-terminals
	/// Sigma = alphabet
	/// P = rules
	/// S = start non-terminal
	/// e.g. ({1,2,3}, {a,b,c}, P, 1)
	/// P = "${1}->${2}${3}\n${2}->a${2}\n${2}->e\n${3}->${3}b\n${3}->e"
	/// a^nb^m, n >= 0, m >= 0
	/// Grammar constructor
	/// \param _grammar - Grammar in this form (N, Sigma, P, S)
	/// \param _rules - Rules of Grammar
	Grammar(const std::string & _grammar, const std::string & _rules);
	virtual void Generator(const std::string &);
	virtual Grammar* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual Grammar* Clone() const;
	virtual ~Grammar();
};

#endif
