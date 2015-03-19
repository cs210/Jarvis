# Jarvis
Repo for Team Jarvis

## EditorPrototype
Unreal project that uses the Xbox 360 controller to move and scale objects.

## SpeechRecognition
### Voce
We intend to use Voce as the speech recognition library in the backend

### SpeechRecognitionPlugin
A custom plugin to integrate Speech Recognition into Unreal Engine 4

In order to use the plugin, follow these steps:

1. Go to Window->Plugins->SpeechRecognition and enable the plugin. Restart the UE editor to enable the plugin
2. Choose an actor (or a define a new one) in the level being edited
3. Open the blueprint for the actor and click on the Components tab on the top-right
4. From the panel on the left, choose Add Component and select Speech Input Controller listed under the Input section
5. Click on Blueprint Props on the top left. 
6. In the Details panel that opens up in the bottom left, scroll down to the Interfaces section. Click on the Add button and choose Speech Event Interface.
7. Save and compile the actor's blueprint.
8. Now, the speech input events can be accessed in any blueprint. For example, right-click on a blueprint and search for Speech Input Event. It would list a set of events that are triggered by speech input.
