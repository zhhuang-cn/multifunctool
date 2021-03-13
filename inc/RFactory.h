#ifndef __XFACTORY_H__
#define __XFACTORY_H__

class RTask;
class RFactory
{
public:
	static RFactory* Get()
	{
		if (instance == nullptr)
			instance = new RFactory();
		return instance;
	}
	RTask* Create();

	class AutoCleanup {
		~AutoCleanup() {
			if (RFactory::instance)
			{
				delete RFactory::instance;
				RFactory::instance = nullptr;
			}
		}
	};
private:
	static RFactory* instance;
	static RFactory autoClean;
};


#endif // !__XFACTORY_H__


