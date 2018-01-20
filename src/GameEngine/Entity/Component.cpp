#include "Component.h"


const std::size_t ge::Component::Type = std::hash<std::string>()(TO_STRING(Component));

CLASS_DEFINITION(ge::Component, ge::Position)
CLASS_DEFINITION(ge::Component, ge::Velocity)
CLASS_DEFINITION(ge::Component, ge::Sprite)
CLASS_DEFINITION(ge::Component, ge::Text)
CLASS_DEFINITION(ge::Component, ge::Input)
CLASS_DEFINITION(ge::Component, ge::Animator)
CLASS_DEFINITION(ge::Component, ge::Collider)



/*
	Position Member functions
*/

ge::Position::Position() : Component("Position")
{
	this->m_pos = Vector2f(0, 0);
}

ge::Position::Position(const Vector2f& rhs) : Component("Position")
{
	this->m_pos = rhs;
}

ge::Position::~Position()
{

}

void ge::Position::UpdatePos(ge::Vector2f const & v, uint32_t widht, uint32_t height, uint32_t offset)
{
	this->m_pos.x += v.x;
	this->m_pos.y += v.y;
	if (this->m_pos.x < 0)
		m_pos.x = 0;
	if (this->m_pos.y < 0)
		m_pos.y = 0;
	if (this->m_pos.x > widht - offset)
		m_pos.x = widht - offset;
	if (this->m_pos.y > height - offset)
		m_pos.y = height - offset;
}

ge::Vector2f ge::Position::getPos() const
{
	return (this->m_pos);
}

/*
	Velocity Member functions
*/

ge::Velocity::Velocity() : ge::Component("Velocity")
{
	this->m_pos = ge::Vector2f(0, 0);
}

ge::Velocity::Velocity(const ge::Vector2f& rhs) : ge::Component("Velocity")
{
	this->m_pos = rhs;
}

ge::Velocity::~Velocity()
{

}

void ge::Velocity::UpdateVel(float const v)
{
	this->m_pos.x /= v;
	this->m_pos.y /= v;
}

ge::Vector2f ge::Velocity::getVel() const
{
	return (this->m_pos);
}

/*
	Sprite Member Functions
*/

ge::Sprite::Sprite(std::string const & t_textureName, uint32_t const t_priority) : ge::Component("Sprite"), textureName(t_textureName), priority(t_priority)
{
}

ge::Sprite::~Sprite()
{

}

/*
	Text Member Functions
*/

ge::Text::Text(std::string const & t_text, std::string const & t_fontName) : ge::Component("Text"), text(t_text), fontName(t_fontName)
{
}

ge::Text::~Text()
{

}

/*
	Input Member Functions
*/

ge::Input::Input(int t_inputId) : ge::Component("Input"), id(t_inputId)
{
}

ge::Input::~Input()
{

}


/*
	Animator memver functions
*/

ge::Animator::Animator() : ge::Component("Animator")
{

}

ge::Animator::~Animator()
{

}

void ge::Animator::AddAnimation(std::string const & name, Animation const & animation) {
	animations_.insert(std::pair<std::string, ge::Animation>(name, animation));
}

void ge::Animator::SetAnimation(std::string const & name) {
	if (currents_.empty() || name != currents_.top()) {
		if (!animations_.count(name)) {
			ErrorUnknownAnimation_(name);
		}
		currents_ = std::stack<std::string>();
		currents_.push(name);
		time_ = std::chrono::high_resolution_clock::now();
	}
}

void ge::Animator::DoOnce(std::string const & name) {
	if (currents_.empty() || name != currents_.top()) {
		if (!animations_.count(name)) {
			ErrorUnknownAnimation_(name);
		}
		currents_.push(name);
		time_ = std::chrono::high_resolution_clock::now();
	}
}

std::string ge::Animator::GetSprite() {
	if (currents_.empty()) {
		ErrorNoAnimation_();
		return "";
	}
	if (animations_.count(currents_.top())) {
		ge::Animation & animation = animations_[currents_.top()];
		while (std::chrono::high_resolution_clock::now() > time_) {
			time_ += std::chrono::milliseconds(animation.speed);
			if (animation.current + 1 >= animation.sprites.size()) {
				animation.current = 0;
				if (currents_.size() > 1) {
					currents_.pop();
				}
			}
			else {
				++animation.current;
			}
		}
		return animation.sprites[animation.current];
	}
	else {
		ErrorUnknownAnimation_("currents_");
		return "";
	}
}

int32_t ge::Animator::GetPriority() const {
	if (currents_.empty()) {
		ErrorNoAnimation_();
		return 0;
	}
	if (animations_.count(currents_.top())) {
		return animations_.at(currents_.top()).priority;
	}
	else {
		ErrorUnknownAnimation_(currents_.top());
		return 0;
	}
}

void ge::Animator::ErrorUnknownAnimation_(std::string const & name) const {
	std::cerr << "Animator : Animation " << name << " doesn't exist" << std::endl;
}

void ge::Animator::ErrorNoAnimation_() const {
	std::cerr << "Animator : No animation set" << std::endl;
}

ge::Animator::AnimationsList const & ge::Animator::GetAnimationsList() const {
	return animations_;
}


/*
	Collider Member Functions
*/
ge::Collider::Collider(Vector2f const & t_topLeft, Vector2f const & t_bottomRight, std::string const & t_tag) : ge::Component("Collider"), position_(t_topLeft), size_(t_bottomRight), tag_(t_tag)
{
}

ge::Collider::~Collider()
{

}
ge::Collision & ge::Collider::CollisionPrediction(std::unique_ptr<GameObject> const & t_current, std::string const & t_tagToCheck, std::vector<std::unique_ptr<ge::GameObject>> const & t_gameObjects)
{
	Collision col{Vector2f(-1,-1), 0};

	for (auto const & it : t_gameObjects)
	{
		if (&it->GetComponent<Collider>() != nullptr)
		{
			if (it->GetComponent<Collider>().tag_ == t_tagToCheck)
			{
				if (AABBCircleIntersecQuick(it->GetComponent<Position>().getPos(), it->GetComponent<Collider>().size_, t_current->GetComponent<Position>().getPos(), t_current->GetComponent<Velocity>().getVel().length()))
				{
					Vector2f CurrentPos = t_current->GetComponent<Position>().getPos();
					Vector2f BotRight = t_current->GetComponent<Collider>().size_;
					Vector2f CurrentVel = t_current->GetComponent<Velocity>().getVel();
					col.point = VectorIntersec(CurrentPos, Vector2f(CurrentPos.x + BotRight.x, CurrentPos.y), it->GetComponent<Position>().getPos(), Vector2f(it->GetComponent<Position>().getPos().x, it->GetComponent<Position>().getPos().y + it->GetComponent<Collider>().size_.y));
					if (col.point.x != -1)
						return (col);
					col.point = VectorIntersec(Vector2f(CurrentPos.x, CurrentPos.y + BotRight.y), Vector2f(CurrentPos.x + BotRight.x, CurrentPos.y + BotRight.y), it->GetComponent<Position>().getPos(), Vector2f(it->GetComponent<Position>().getPos().x, it->GetComponent<Position>().getPos().y + it->GetComponent<Collider>().size_.y));
					if (col.point.x != -1)
						return (col);
				}
			}
		}
		col.index++;
	}
	return (col);
}

ge::Vector2f ge::Collider::VectorIntersec(Vector2f const & uStart, Vector2f const & uEnd, Vector2f const & vStart, Vector2f const & vEnd)
{
	Vector2f u = uEnd - uStart;
	Vector2f v = vEnd - vStart;

	double DotProduct = (u.x * v.y) - (v.x * u.y);
	if (DotProduct == 0)
		return (Vector2f(-1, -1));
	bool positive = DotProduct > 0;

	Vector2f s = uStart - vStart;
	double snumer = (u.x * s.y) - (s.x * u.y);
	if ((snumer < 0) == positive)
		return (Vector2f(-1, -1));

	double tnumer = (v.x * s.y) - (s.x * v.y);
	if ((tnumer < 0) == positive)
		return (Vector2f(-1, -1));
	if (((snumer > DotProduct) == positive) || ((tnumer > DotProduct) == positive))
		return (Vector2f(-1, -1));

	double t = tnumer / DotProduct;
	Vector2f intersection = Vector2f(uStart.x + (t *u.x), uStart.y + (t *u.y));
	return (intersection);
}

bool ge::Collider::AABBCircleIntersecQuick(Vector2f const &topLeftAABB, Vector2f const & AABBSize, Vector2f const & circleCenter, double radius)
{
	Vector2f AABBCenter = Vector2f(topLeftAABB.x + AABBSize.x, topLeftAABB.y + AABBSize.y);
	AABBCenter.x = AABBCenter.x - (AABBSize.x / 2);
	AABBCenter.y = AABBCenter.y - (AABBSize.y / 2);
	double AABBRadius = Vector2f(topLeftAABB.x - AABBCenter.x, topLeftAABB.y - AABBCenter.y).length();
	double dx = circleCenter.x - AABBCenter.x;
	double dy = circleCenter.y - AABBCenter.y;
	double dist = sqrtf(dx * dx + dy * dy);
	return (dist < AABBRadius + radius);
}


/*
	GameObject non-templeted member functions
*/

void ge::GameObject::setTag(std::string const & t_tag)
{
	this->m_tag_ = t_tag;
}

std::string const & ge::GameObject::getTag() const
{
	return (this->m_tag_);
}
