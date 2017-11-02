#include"Test.h"
#include"Range.h"
#include"Grammar.h"
#include"ConstPrimitiveTest.h"
#include"Delimiter.h"

Grammar::Grammar(const std::string & _grammar, const std::string & _rules)
	: grammar_(_grammar)
	, rules_(_rules + '\n')
{
	this->GrammarParsing();
	// this->Generate();
}
void Grammar::RuleParsing(const std::string & _rule)
{
	if (_rule.size() < 7) // ${a}->b
		return;
	std::string rule = _rule;
	rule.erase(std::remove_if(rule.begin(), rule.end(), isspace), rule.end());
	size_t index_of_arrow = rule.find_first_of("->");
	std::string left_part = rule.substr(0, index_of_arrow);
	std::string right_part = rule.substr(index_of_arrow + 2);
	std::string name_of_nonterm;
	if (left_part[0] == '$' && left_part[1] == '{' && left_part.back() == '}')
	{
		name_of_nonterm = left_part.substr(2);
		name_of_nonterm.pop_back();
		THROW(names_of_nonterm_.find(name_of_nonterm) == names_of_nonterm_.end(), "Wrong nonterm element");
	}
	else
	{
		THROW(true, "Wrong left part");
	}
	parsed_rules_[name_of_nonterm].push_back(right_part);
}
void Grammar::NonTermsParsing(const std::string & _nonterms)
{
	if (_nonterms[0] == '{' && _nonterms.back() == '}')
	{
		std::string writable_nonterms = _nonterms;
		writable_nonterms.erase(0, 1);
		writable_nonterms.pop_back();
		char delimiter = ',';
		size_t pos, last_pos = 0;
		while ((pos = writable_nonterms.find(delimiter, last_pos)) != std::string::npos) {
			std::string nonterm = writable_nonterms.substr(last_pos, pos - last_pos);
			names_of_nonterm_.insert(nonterm);
			last_pos = pos + 1;
		}
		std::string nonterm = writable_nonterms.substr(last_pos);
		names_of_nonterm_.insert(nonterm);
	}
	else
	{
		THROW(true, "Nonterms format error");
	}
}
void Grammar::TermsParsing(const std::string & _terms)
{
	if (_terms[0] == '{' && _terms.back() == '}')
	{
		std::string writable_terms = _terms;
		writable_terms.erase(0, 1);
		writable_terms.pop_back();
		char delimiter = ',';
		size_t pos, last_pos = 0;
		while ((pos = writable_terms.find(delimiter, last_pos)) != std::string::npos) {
			std::string term = writable_terms.substr(last_pos, pos - last_pos);
			THROW(term.size() != 1, "Term length must be equal to 1");
			terms_.insert(term[0]);
			last_pos = pos + 1;
		}
		std::string term = writable_terms.substr(last_pos);
		THROW(term.size() != 1, "Term length must be equal to 1");
		terms_.insert(term[0]);
	}
	else
	{
		THROW(true, "Terms format error");
	}
}
void Grammar::StartNonTermParsing(const std::string & _start_nonterm)
{
	THROW(names_of_nonterm_.find(_start_nonterm) == names_of_nonterm_.end(), "Start nonterm not a valid nonterm");
	start_nonterm_ = _start_nonterm;
}
void Grammar::GrammarParsing()
{
	grammar_.erase(std::remove_if(grammar_.begin(), grammar_.end(), isspace), grammar_.end());


	size_t index_of_brace = grammar_.find_first_of('}'), last_brace_index = 0;

	std::string nonterminals = grammar_.substr(last_brace_index + 1, index_of_brace - last_brace_index);
	this->NonTermsParsing(nonterminals);

	last_brace_index = ++index_of_brace;
	index_of_brace = grammar_.find_first_of('}', index_of_brace + 1);
	std::string alphabet = grammar_.substr(last_brace_index + 1, index_of_brace - last_brace_index);
	this->TermsParsing(alphabet);

	last_brace_index = ++index_of_brace;
	index_of_brace = grammar_.find_first_of(',', index_of_brace + 1);
	std::string start_nonterminal = grammar_.substr(index_of_brace + 1);
	start_nonterminal.pop_back();
	this->StartNonTermParsing(start_nonterminal);

	char delimiter = '\n';
	size_t pos = 0, last_pos = 0;
	while ((pos = rules_.find(delimiter, last_pos)) != std::string::npos) {
		std::string rule = rules_.substr(last_pos, pos - last_pos);
		this->RuleParsing(rule);
		last_pos = pos + 1;
	}
	std::string rule = rules_.substr(last_pos);
	this->RuleParsing(rule);
}
void Grammar::Generator(const std::string & _current_nonterm)
{
	THROW(names_of_nonterm_.find(_current_nonterm) == names_of_nonterm_.end(), "Error when trying parse the nonterm " + _current_nonterm + ": that nonterm not present in grammar.");
	THROW(parsed_rules_.find(_current_nonterm) == parsed_rules_.end(), "Error when trying parse the nonterm " + _current_nonterm + ": that nonterm not present in rules.");
	size_t rule_number = Rand() % parsed_rules_[_current_nonterm].size();
	std::string rule = parsed_rules_[_current_nonterm][rule_number];
	if (rule == "e")
	{
		return;
	}
	enum variable_status {not_variable = 0, dollar_sign_readed = 1, open_brace_readed = 2, close_brace_readed = 3};
	variable_status variable_state = not_variable;
	std::string variable = "";
	for (unsigned int i = 0; i < rule.size(); i++)
	{
		if (rule[i] == '$')
		{
			variable_state = dollar_sign_readed;
			continue;
		}
		else if (rule[i] == '{')
		{
			if (variable_state == dollar_sign_readed)
			{
				variable_state = open_brace_readed;
				continue;
			}
			else
			{
				if (terms_.find('{') != terms_.end())
				{
					Delimiter* brace_char = new Delimiter('{');
					this->Add(brace_char);
					delete brace_char;
					continue;
				}
				THROW(true, "Open brace character do not present in alphabet.");
			}
		}
		else if (rule[i] == '}')
		{
			if (variable_state == open_brace_readed)
			{
				variable_state = close_brace_readed;
				this->Generator(variable);
				variable = "";
				variable_state = not_variable;
				continue;
			}
		}
		else
		{
			if (variable_state == open_brace_readed)
			{
				variable += rule[i];
			}
			else
			{
				if (terms_.find(rule[i]) != terms_.end())
				{
					ConstPrimitiveTest<char>* character = new ConstPrimitiveTest<char>(rule[i]);
					this->Add(character);
					delete character;
					continue;
				}
				THROW(true, rule[i] + " character do not present in alphabet.");
			}
		}
	}
}
Grammar* Grammar::Generate()
{	
	this->Clear();
	this->Generator(start_nonterm_);

	std::ostringstream out;
	CompositeTest::Print(out);
	result_ = out.str();
	test_generated_ = true;
	return this;
}
void Grammar::Print(std::ostream& _out) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	_out << result_;
}
Grammar* Grammar::Clone() const
{
	Grammar* grammar = new Grammar(grammar_, rules_);
	grammar->parsed_rules_ = parsed_rules_;
	grammar->names_of_nonterm_ = names_of_nonterm_;
	grammar->terms_ = terms_;
	grammar->start_nonterm_ = start_nonterm_;
	grammar->current_string_ = current_string_;
	return grammar;
}
Grammar::~Grammar()
{
}