//
//  Singleton.h
//  BlackDogEngine
//
//  Created by Diego Jesus on 01/07/15.
//
//

#ifndef BlackDogEngine_Singleton_h
#define BlackDogEngine_Singleton_h

namespace bde {
    template<class T>
    class Singleton{
    private:
        Singleton(Singleton const &) = delete;
        void operator=(Singleton const& s) = delete;
    protected:
        Singleton(){};
        virtual ~Singleton(){};
    public:
        
        static std::shared_ptr<T> Instance(){
            static std::shared_ptr<T> instance = std::make_shared<T>();
            
            return instance;
        }
    };
}

#endif
