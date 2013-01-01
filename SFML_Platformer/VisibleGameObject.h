#pragma once
class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	std::string name;
	virtual void Load(std::string filename);
	void Draw(sf::RenderWindow & window);
	virtual void Update(sf::Time elapsedTime);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsLoaded() const;
	sf::Sprite& GetSprite();
	sf::RectangleShape& GetShape();
	sf::FloatRect GetBounds();

protected:
	virtual void SetPosition(sf::Vector2f);
	sf::RectangleShape _shape;
	bool _isShape;

private:
	sf::Sprite  _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;

};
