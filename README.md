# Jarvis
Repo for Team Jarvis

## Editor
Unreal Engine level editing project. Uses the Razer Hydra.

## EditorPrototype
Unreal project that uses the Xbox 360 controller to move and scale objects. Deprecated.

## SpeechRecognition
### Voce
We intend to use Voce as the speech recognition library in the backend

### SpeechRecognitionPlugin
A custom plugin to integrate Speech Recognition into Unreal Engine 4

To build the plugin:

1. Copy the **SpeechRecognitionPlugin** folder (present in the repo) to **<UE-Code-Root-Dir>/Engine/Plugins**
2. Run GenerateProjectFiles.bat from **<UE-Code-Root-Dir>**
3. Open **<UE-Code-Root-Dir>/UE4.sln** using Visual Studio 2013
4. Set the solution configuration to **Development Editor** (This can be done from the drop-down in the toolbar on top)
5. Build the UE4 project

In order to use the plugin in UE4, follow these steps in the editor:

1. Go to **Window->Plugins->SpeechRecognition** and enable the plugin. Restart the UE editor to enable the plugin
2. Choose an actor (or a define a new one) in the level being edited
3. Open the blueprint for the actor and click on the **Components** tab on the top-right
4. From the panel on the left, choose **Add Component** and select **Speech Input Controller** listed under the **Input** section
5. Click on **Blueprint Props** on the top left. 
6. In the **Details** panel that opens up in the bottom left, scroll down to the Interfaces section. Click on the **Add** drop-down menu and choose **Speech Event Interface**.
7. Save and compile the actor's blueprint.
8. Now, the speech input events can be accessed in any blueprint. For example, right-click on a blueprint and search for Speech Input Event. It would list a set of events that are triggered by speech input.
