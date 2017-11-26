#pragma once
#include "CardManager.hpp"

class CardHandler
{
public:
	static void Init(CardManager* cardManager);

	CardHandler();
	const std::unique_ptr<Card>& getCard(unsigned int cardPosition) const;
	void addCards(std::vector<unsigned int> cards) const;
	unsigned int getMapPosition() const;
	void moveCardTo(unsigned int cardPosition, CardHandler* handlerDestination, unsigned int destination) const;
	unsigned int lastPosition() const;


private:
	static CardManager* m_manager;

	unsigned int m_map_position;
};
