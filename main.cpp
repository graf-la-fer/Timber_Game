#include <sstream>
#include <SFML/Graphics.hpp>
// Make code easier to type with "using namespace"
using namespace sf;


// Function declaration
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
// Where is the player/branch?
// Left or Right
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

// This is where our game starts from
int main()
{
	// Create a video mode object
	VideoMode vm(1900, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// �������� �������� ��� ����������� ������� �� ����������� ����������
	Texture textureBackground;
	// �������� ������������ ����������� � ��������
	textureBackground.loadFromFile("graphics/background.png");
	// �������� �������
	Sprite spriteBackground;
	// ������������ �������� � �������
	spriteBackground.setTexture(textureBackground);
	// ��������� ������� ������� spriteBackground 
	spriteBackground.setPosition(0, 0);

	// �������� ������� ������
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// ������ �����
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	// ��������� �������� �����
	bool beeActive = false;
	// �������� ������
	float beeSpeed = 0.0f;

	// 3 ������� ������� �� 1 ��������
	Texture textureCloud;
	// �������� �������� ������
	textureCloud.loadFromFile("graphics/cloud.png");
	// 3 ������� �������
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	// ������������ - �����
	// �� �� ������ ������
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	// ��������� ��������� ������ �� ������
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	// �������� �������
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// ���������� ��� ���������� ����� ��������
	Clock clock;

	// ��������� �����
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// �������� �� ���� 
	bool paused = true;

	// ������� ��������� ���������
	int score = 0;
	Text messageText;
	Text scoreText;
	// ����� ������
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	// ��������� ������ ��� ���������
	messageText.setFont(font);
	scoreText.setFont(font);
	// ��������� ���������
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");
	// �������� ���������
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	// ����� �����
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// ������� ������
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);


	// ���������� 6 �����
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	// ��������� �������� ��� ������� �������
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		// ��������� ������ ������� � ������� �����
		// ����� �� ����� ������� ���, �� ����� ��� ���������.
		branches[i].setOrigin(220, 20);
	}

	updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);


	// ���������� ������
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	// ����� �������� �����
	side playerSide = side::LEFT;
	// ���������� ���������
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);
	// ���������� ������
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);
	// ��������� ����� �� ������
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;
	// ���������� ������
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);
	// ��������� ����������
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	// �������� �����
	bool acceptInput = false;

	while (window.isOpen())
	{
		/*
		****************************************
		������������ �������� �������� ������
		****************************************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			// ����� ������� � �����
			score = 0;
			timeRemaining = 6;

		}

		// ������ ��� ����� -
		// ������� �� ������ �������

		for (int i = 1; i < NUM_BRANCHES; i++)
		{
			branchPositions[i] = side::NONE;
		}
		// ���������, ��� ������ ���������
		spriteRIP.setPosition(675, 2000);
		// ����������� ������ � �������� ���������
		spritePlayer.setPosition(580, 720);
		acceptInput = true;

		// Wrap the player controls to
		// Make sure we are accepting input
		if (acceptInput)
		{
			// ��������� ������ ������� ����
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// ���������, ��� ����� ������
				playerSide = side::RIGHT;
				score++;
				// �������� �����
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);
				// �������� �����
				updateBranches(score);

				// ��������� ������ �����
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;
				acceptInput = false;
			}
			// ���������� ����� �������� ����
		}

		/*
		****************************************
		�������� �����
		****************************************
		*/

		if (!paused)
		{
			// ����� ���������
			Time dt = clock.restart();

			// ��������� �� ����������� ������� ���������
			timeRemaining -= dt.asSeconds();
			// ��������� ������� ��������� �����
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining,
				timeBarHeight));

			if (timeRemaining <= 0.0f) {

				// �����
				paused = true;
				// ��������� ��� ������������
				messageText.setString("Out of time!!");
				//��������� ������ ������ � ��� ����� ��������
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			}
			// ��������� �����
			if (!beeActive)
			{
				// ��������
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;
				// ������
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
				// ����������� �����
			{
				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);
				// �������� �� ������ ����?
				if (spriteBee.getPosition().x < -100)
				{
					// ���������� � ���������� �����
					beeActive = false;
				}
			}

			// ���������� ��������
			// Cloud 1
			if (!cloud1Active)
			{
				// ��������
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);
				// ������
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else
			{
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);
				// ������� �� ������
				if (spriteCloud1.getPosition().x > 1920)
				{
					// ���������� � ��� �������� � ��������� �����
					cloud1Active = false;
				}
			}

			// Cloud 2
			if (!cloud2Active)
			{
				// ��������
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);
				// ������
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);
				// ������� �� ������
				if (spriteCloud2.getPosition().x > 1920)
				{
					// ���������� � ��� �������� � ��������� �����
					cloud2Active = false;
				}
			}
			if (!cloud3Active)
			{
				// ��������
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);
				// ������
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);
				// ������� �� ������
				if (spriteCloud3.getPosition().x > 1920)
				{
					// ���������� � ��� �������� � ��������� �����
					cloud3Active = false;
				}
			}

			// Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			// ���������� �������� �����
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					// ����������� ������ �����
					branches[i].setPosition(610, height);
					// ����������� ������ � ������ �������
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// ����������� ������ ������
					branches[i].setPosition(1330, height);
					// ������� �������� � �������� ���������
					branches[i].setRotation(0);
				}
				else
				{
					// ������ �����
					branches[i].setPosition(3000, height);
				}
			}

		} // End if(!paused)
		/*
		****************************************
		��������� �����
		****************************************
		*/
		// �������� ��� � ���������� �����
		window.clear();
		
		// ��������� ������� �����
		window.draw(spriteBackground);

		// Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}

		// Draw the tree
		window.draw(spriteTree);

		// Draw the player
		window.draw(spritePlayer);
		// Draw the axe
		window.draw(spriteAxe);
		// Draw the flying log
		window.draw(spriteLog);
		// Draw the gravestone
		window.draw(spriteRIP);
		// Draw the bee
		window.draw(spriteBee);

		// Draw the insect
		window.draw(spriteBee);

		// Draw the score
		window.draw(scoreText);

		// Draw the timebar
		window.draw(timeBar);

		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// �������� ���, ��� �� ������ ��� ����������
		window.display();
	}


	return 0;
}

// Function definition
void updateBranches(int seed)
{
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}
	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}