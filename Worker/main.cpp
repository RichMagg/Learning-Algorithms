#include <iostream>
#include <queue>
#include <optional>
#include <memory>
#include <algorithm>

class Work
{
private:
	std::string m_name;
	int m_salary;

public:
	Work(std::string name, int salary)
	{
		m_name = name;
		m_salary = salary;
	}

	const std::string &getName() const { return m_name; }
	const int &getSalary() const { return m_salary; }
};

class Person
{
private:
	std::string m_name;
	int m_age;
	std::vector<std::shared_ptr<Person>> m_friends;
	std::optional<Work> m_work;

public:
	Person(std::string name, int age, std::optional<Work> work = std::nullopt)
	{
		m_name = name;
		m_age = age;
		m_friends = {};
		m_work = (age >= 18) ? work : std::nullopt;
	}

	const std::string &getName() const { return m_name; }
	const int &getAge() const { return m_age; }
	const std::optional<Work> &getWork() const { return m_work; }
	std::vector<std::shared_ptr<Person>> &getFriends() { return m_friends; }

	bool operator==(const Person &other) const
	{
		bool same_work = false;

		if (!m_work && !other.m_work)
		{
			same_work = true;
		}
		else if (m_work && other.m_work)
		{
			same_work = (m_work->getName() == other.m_work->getName() &&
						 m_work->getSalary() == other.m_work->getSalary());
		}

		return (m_name == other.m_name && m_age == other.m_age && same_work);
	}

	void addNewFriend(std::shared_ptr<Person> new_friend)
	{
		for (const auto &f : m_friends)
		{
			if (f == new_friend)
				return;
		}
		m_friends.push_back(new_friend);
	}
};

std::optional<std::shared_ptr<Person>> findAWorker(std::shared_ptr<Person> first_person)
{
	std::queue<std::shared_ptr<Person>> search_queue;
	std::vector<std::shared_ptr<Person>> checked;

	search_queue.push(first_person);

	for (const auto &f : first_person.get()->getFriends())
	{
		search_queue.push(f);
	}

	while (!search_queue.empty())
	{
		auto current_person = search_queue.front();
		search_queue.pop();

		auto it = std::find(checked.begin(), checked.end(), current_person);

		// Person not checked
		if (it == checked.end())
		{
			if (current_person.get()->getWork())
			{
				return current_person;
			}

			for (const auto &f : current_person.get()->getFriends())
			{
				search_queue.push(f);
			}
			checked.push_back(current_person);
		}
	}
	return std::nullopt;
}

int main(int argc, char *argv[])
{
	auto bob = std::make_shared<Person>("Bob", 20, Work("Programmer", 4500));
	auto larry = std::make_shared<Person>("Larry", 19);
	auto john = std::make_shared<Person>("John", 22);

	bob->addNewFriend(larry);
	bob->addNewFriend(john);
	
	larry->addNewFriend(john);
	larry->addNewFriend(bob);
	
	john->addNewFriend(larry);
	john->addNewFriend(bob);
	
	auto worker = findAWorker(john);

	if (worker)
	{
		std::cout << "Worker found: " << worker->get()->getName() << std::endl;
		std::cout << "Salary: $" << worker->get()->getWork()->getSalary() << std::endl;
	}
	else
	{
		std::cout << "No worker found!" << std::endl;
	}
	
	return 0;
}