![logo](https://github.com/user-attachments/assets/d6219f88-cf7a-4e76-a408-5f39f748658f)

## Introduction
**Ishtar Engine** is a Game Engine made using C++ and OpenGL, which can be used to create interactive applications, well technically video games. To put it straight Ishtar engine has capabilities of creating a game with some technical features a game has to offer.



<ins>**How to start the application**</ins>

Clone the Repo with your desired Version Control application and Use Visual Studio 2022 and Set the C++ version to CPP17 and the Project Configuration to Release

## Engine Structure

Ishtar Engine Heavily relies on Inheritance, Polymorphism and Heap Memory Allocation with Pointers. Below you will know how to properly create a scene for yourself if you want to work with a new feature which won't disturb other features.

<ins>**Scene Creation**</ins>

* Inside the project you can find a folder named Scene Manager and you can find all the scene in there that I'm using to implement different features. All you have to do is create class with desired name and inherit the base scene class and override it's virtual functions likeso,

```c++
//Inheriting the BaseScene to start working in your own Scene
#include "../BaseScene.h"
class YourSceneName : public BaseScene
{

public:
	YourSceneName(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
private:


};

```

**For any new blooming C++ developers, Congratulations You just learned the basic concept of Inheritance, Polymorphism and Enacapsulation by doing this lol**

* Okay lets continue, now create declarations for the functions and write your definitions you want. The Start() function is used to declare any values or setting positions... the Update() function is called inside with while loop to update every frame and the Render() function is used to render any Scene UI elements that you want to display for example the engine grid, Light UI Element etc.

```c++
SceneEight::SceneEight(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
   // Initialize any values you want when the class is created
}

SceneEight::~SceneEight()
{
   // Make sure to clean up any pointers you created
}

void SceneEight::Start()
{


    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));

    Model* orc = new Model();
    orc->LoadModel("Models/Character/Enemy/Animations/Orc.fbx");
    orc->transform.SetPosition(glm::vec3(-75.91, 5.82, 105.85));
    orc->transform.SetScale(glm::vec3(0.01));
    GraphicsRender::GetInstance().AddModelAndShader(orc, application->defaultShader);

}

void SceneEight::Update()
{
   // Calls Every Frame like Unity's Update
}

void SceneEight::Render()
{
   // Display any Scene UI Elements
}

```
With the Above code you've just created a Directional Light and an example model for the scene. If you copy paste the code in your system it would probably not work as the folder structures may change so keep an eye out for the directory paths I've used.

* Now to instantiate the scenes you find the Rendering Pipeling folder and open the BaseRenderingPipline script. Now find the Start Function and create a pointer to the base class and use it to point the derived class you created likeso,


```c++
void BaseRenderingPipeline::Start()
{

    BaseScene* exampleScene = new YourSceneName("SomeName");
    SceneManager::GetInstance().OnChangeScene("SomeName");
}

```

Make sure you call the OnChangeScene() Function from the scene manager to call the scene when the application starts.

That is all you need to do to start working in a Scene separately.


## Engine Features Till Date

The Engine has some handful of features implemented until now and I'm steadily working on more new features and new shaders with industry standard techniques. I'm constantly learning new methods and techniques in Graphics Programming and it's really exciting honestly! Below you'll find the Features that I've implemented. You can find exciting stuff if you surf through my engine.

<ins>**Graphics Stuff**</ins>

* Off Screen Rendering
* Frustrum Culling
* Mesh Instancing
* Post Processing
* Level Of Detail
* Skeletal Animation
* Shadows
* Deferred Rendering
* ImGUI Panels and Content Browser

<ins>**Physics Stuff**</ins>
* PhysX Integration
* Softbody Physics Simulation
* Bounding Volume Hierarchy Collision

<ins>**Shaders With GLSL**</ins>
* Interior Mapping

<ins>**Engine Specific**</ins>
* Particle System
* FMOD audio 


You can learn more about how I implemented each of the feature in my portfolio. Click this Link to open my Portfolio: https://uphendhra.wixsite.com/website
