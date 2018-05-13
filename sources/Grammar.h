#ifndef GRAMMAR___
#define GRAMMAR___

#include "CompositeTest.h"

class Grammar : public CompositeTest
{
protected:
	std::string grammar_, rules_;
	// grammar G = (N, Sigma, P, S)
	// N = non-terminals
	// Sigma = alphabet
	// P = rules
	// S = start non-terminal
	// e.g. ({1,2,3}, {a,b,c}, P, 1)
	// P = "${1}->${2}${3}\n${2}->a${2}\n${2}->e\n${3}->${3}b\n${3}->e"
	// a^nb^m, n >= 0, m >= 0
	std::map<std::string, std::vector<std::string> > parsed_rules_;
	std::set<std::string> names_of_nonterm_;
	std::set<char> terms_;
	std::string start_nonterm_;
	std::string current_string_;
public:

	Grammar(const std::string &, const std::string &);
	virtual void Generator(const std::string &);
	virtual Grammar* Generate();
	virtual void NonTermsParsing(const std::string &);
	virtual void StartNonTermParsing(const std::string &);
	virtual void TermsParsing(const std::string &);
	virtual void RuleParsing(const std::string &);
	virtual void GrammarParsing();
	virtual void Print(std::ostream& = std::cout) const;
	virtual Grammar* Clone() const;
	virtual ~Grammar();
};

#endif