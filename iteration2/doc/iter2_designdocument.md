# Design Justifications for FlashPhoto
#### Group Name:
Group C-10

#### Members:
- Blake Sartor
- Zechariah Nelson
- Raghav Mutneja

#### Instructions 
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.  
> A few tips to maximize the success of your design document:  
>   1. Make sure the **description** of your design decision only contains an objective description of how you structured your design and how it was implemented (specifically how your solution solves the problem given in the prompt). Save any arguments in favor of your design for the **justification** section.
>
>   2. Your justification will probably need to compare against at least one alternative, and you will need to provide a compelling argument for why your solution is better than the alternative.
>
>   3. Edit this file when writing your design document. Do not move or rename this file. Do not direct to any outside resources for your images or code. Place all images and code in this document. Please match the formatting of the [Example Design Document](https://github.umn.edu/umn-csci-3081F16/Example-Design-Document/blob/master/doc/DesignDocument.md) and [its source](https://raw.github.umn.edu/umn-csci-3081F16/Example-Design-Document/master/doc/DesignDocument.md?token=AAADyd5L8wd57F_qLX4Nf-2nVvfRlMj5ks5YH-qHwA%3D%3D) as precisely as possible, especially in regards to:
>     - **Formatting code** (do not include images of your code, make sure that your code is formatted with C++ coloring)
>     - **Inserting images**
>     - **Numbered lists for your tutorial**
>     - **Captioning your Figures**
>     - **Including the original prompts in their original quote form**  
> 
>  This formatting helps us grade your assignments effectively, and thus failure to meet these requirements may result in point deductions. Any material that is not presented in this design document will not be graded.
>   4. When including a class diagram, only show the classes and members that convey the point you're trying to make. For example, showing the class BaseGfxApp in a UML diagram will probably not be appropriate.





## 1  Design Question One
> This iteration of the project introduces the concept of filters. You had to implement several filters, which fell into two types: pixel-independent (where each pixel is filtered independently), and convolution-based (where filtering a pixel requires information about its neighboring pixels by means of a kernel). Naturally, a key design decision is how these filters are represented. Each filter has a different algorithm for modifying the canvas, and only some of these algorithms require kernels. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description
> So to begin addressing the filters issue was the prime problem or the prime goal of this iteration. There were two types of filters as described already, ones which were pixel-independent and convolution based. The pixel-based filters comprised of threshold, adjust saturation, adjsut R,G,B levels, quantize and a special filter. On the other hand the convolution filters comprised of blur, sharpen, edge detection and motion blur. So we decided to follow a similar approach as we did for Iteration 1, where we had a Tool class, and all the tools were made into its child classes. So here too we have a Convolution Filter class that inherits from a Filter class, both of which have their children filters as they fall into the respective categories. So for the Filter class, all the filters had an ApplyFilter, which loops through each pixel in the PixelBuffer, and calls ModifyPixel on it, which is overloaded in each child, to use its own algorithm to calculate the pixel's new color. All of the convolution filters have a setMask which actually sets up the kernal, which is useful for dealing with filters that can apply different intensities, like blur, or that can use different algorithms to build their kernal, like motion blur. ApplyFilter loops through each pixel in the PixelBuffer, and calls ApplyKernal on it, which uses the kernal to calculate the pixels new color. 


> The filter manager class contains an instance of each filter, and, it calls ApplyFilter for each one, when the corresponding button is pushed.

> Below are snippets of how each filter has been designed for each category which also portray the different calculating algorithms we used to make each filter work as desired, to begin with the pixel-dependent filters.
#### Threshold 
> Where each of the color channels will be rounded up to the maximum value of 1.0 or down to the minimum value of 0.0 based on whether the pixel’s value is greater or less than the GLUI input value, respectively.
> 
> <img width="718" alt="screen shot 2016-11-21 at 11 01 04 pm" src="https://media.github.umn.edu/user/5701/files/7363fea8-b03e-11e6-9691-7050f35373d7">

> #### Adjust Saturation
> Which either increase, decrease, or invert the colorfulness of your image.
>
> <img width="762" alt="screen shot 2016-11-21 at 11 03 07 pm" src="https://media.github.umn.edu/user/5701/files/b9068b88-b03e-11e6-8cc6-f7d7a972378d">

> #### Adjust R,G,B Levels 
> Which increases/decreases the intensity of each color channel. This should be done by multiplying each channel by its corresponding GLUI input value.
> 
> <img width="896" alt="screen shot 2016-11-21 at 11 04 21 pm" src="https://media.github.umn.edu/user/5701/files/e2590100-b03e-11e6-8472-3478fa97b924">

> #### Quantize 
> Which reduces the number of possible colors by binning each color value into the the number of bins specified. So for instance, if using 4 bins, there will only be 4 possible intensity values for each color channel, spaced evenly: 0%, 33%, 66%, and 100%.
> 
> <img width="728" alt="screen shot 2016-11-21 at 11 05 09 pm" src="https://media.github.umn.edu/user/5701/files/fd414b1c-b03e-11e6-8c7f-62d2a2d2bf64">

> Now for the Convolution filters, which have a similar application:
#### Blur 
> Which blurs the image proportional to the amount specified in the GLUI input. 
> 
> <img width="683" alt="screen shot 2016-11-21 at 11 08 15 pm" src="https://media.github.umn.edu/user/5701/files/717c8212-b03f-11e6-8b12-dd3eb98617b6">

> #### Sharpen 
> Which sharpens the image proportional to the amount specified in the GLUI input.
> 
> <img width="641" alt="screen shot 2016-11-21 at 11 09 35 pm" src="https://media.github.umn.edu/user/5701/files/9c2acb40-b03f-11e6-8bc2-6a7ebc2e00a8">

> #### Edge Detection 
> Which creates a representation of the rate-of-change in the image. Pixels on the border of differently colored regions will be bright, while pixels in areas of low change will be dark.
> 
> <img width="342" alt="screen shot 2016-11-21 at 11 10 54 pm" src="https://media.github.umn.edu/user/5701/files/c9ed0bb0-b03f-11e6-8764-4c536e62b31d">

> #### Motion Blur 
> Which blurs the image in a directional manner. Use the amount specified in the GLUI input as the distance of effect a pixel has in each direction.
> 
> <img width="465" alt="screen shot 2016-11-21 at 11 12 04 pm" src="https://media.github.umn.edu/user/5701/files/f6a28a9a-b03f-11e6-9312-af1b6999fb0b">

> To be more elaborate about the design description below is a UML sketch, which briefly picturizes our idea of how we decided to go about the filters design:
![document1](https://media.github.umn.edu/user/5701/files/af5c1006-b045-11e6-9502-5c4c8ee0185f)


### 1.2 Design Justification

> So we decided to go with a similar design as in Iteration 1 as mentioned earlier. Since we had two types of filters so we created basically 2 types of parent classes which in turn had the different filters as its children. So each filter is a new class for our iteration 2, which inherits from its respective parent class. For instance Blur would inherit from the Convolution Filter class and would have a kernel and a SetMask, while an adjust saturation level filter would inherit from the Filter class and would have a ApplyFilter and a ModifyPixel overloaded.

> The alternative was that instead of having 4-5 separate classes for each filter as children of their parent classes, we could have had all in the parent class and no children, so that would basically be like in the Filter class we have the methods but they just would respond differently rather than being a different method as is the case with our current design. It would be somewhat similar to say having a Duck and not having a different RedHead or MallardDuck, but just having a QuackBehavior in Duck, which would accept different strings for different types of Ducks. The drawback of this design, is that it adds unnecessary complexity. The algorithms used to set up kernals for convolution filters, or to modify pixels for isolated filters would need to be defined somewhere, either in their own child class, or, their own behavior class. The main draw to having behavior classes, is that they make the behavior independent from the class, however, our group was very confident that we would never have to implement a filter class that uses a different filter's kernal. For example, we would never need a blur filter to use a sharpen kernal.  

> Instead of being stored in their own class, the mask generating algorithms could be implemented in the filter_manager class, however, that causes it's own set of issues. The most prominent, is that it ties the process of applying filters to this specific GUI, and, we would need rewrite significant amounts of code to use a different GUI.

> On the other hand our approach solves this problem quite efficiently as its much easier for the user to add a new tool by simply adding a new filter class, and link it to its parent and viola, its done. What the user does with the new filter doesn't affect the rest of the program whatsoever becuase the parent classes don't need any modifications. This makes it a better design decision we felt, and it certainly was easy for us to add to the iteration the code for a new Special filter for example.

> Another alternative solution would be to simply put all of the algorithms in the filter manager class, and run them when the corresponding button is pushed. This solution would have the benefit of a new programmer not needing to look through multiple files to find the algorithm used for each filter. This solution has many other problems, however, such as the fact that it ties all of the filters to this specific GUI. If in a future date, we are required to rearrange buttons, or, put them in some sort of menu, this solution would require major rewriting of code, however, with our solution, none of the filters themselves would have to change at all, only the part that would need to change anyways, in order to get a different GUI layout.

> A final benefit to the solution we chose, is that it matches the solution we chose for implementing tools, back in iteration 1. It doesn't count for too much, but, it is nice to have that symmetry in our source code. It learning how our code works a little easier for new developers.

## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description

> The undo/redo mechanic in this iteration was indeed a different challenge altogether. We implemented this mechanic using a Double-ended Queue (deque). So our undo function undo's the last operation applied to the canvas when the Undo button on the user interface is clicked. In order to do this we needed to save the state of the program whenever a change is made to the canvas. We did this by saving a copy of the PixelBuffer. So we save every undo operation in our deque and make it grow for as long as we have at most 50 undo's in the Undo Deque. Our redo redo's the last undo basically, so doing a redo would basically be rapplying the state that was most recently removed from the canvas by an undo operation. This did sound pretty tricky to do at first but then the Deque had pretty much most of the functionality we needed from a data structure. Why this was the best choice of data structure has been explained later in 2.2 Design Description. 
> Another decision we had to make in designing the undo and redo mechanic, was how to record the different states of the canvas. We chose  to have both undo, and redo hold lists of entire PixelBuffer objects. Whenever undo, or, redo are clicked, the state handler sets the display buffer in FlashPhoto App to the PixelBuffer at the top of the undo, or, redo stack respectively. 
>Finally, we had to decide what to categorize as a change, and, how to inform the deque that a change has been applied to display_buffer_. We wrote another function for the state manager, called ReceivePixelBuffer, that takes a single argument, of a reference to a PixelBuffer object. The function empties the redo deque, and, pushes the PixelBuffer argument into the undo queue, popping the last element, if it contains 50 elements. To ensure that everything appropriate can be undone, Flashphoto_App must call ReceivePixelBuffer before making a significant change to display_buffer_. We defined significant changes as applying any filter, and any brush stroke. To implement this, we called ReceivePixelBuffer in the left mouse down event, and, before every filter application call.

> Lets look at a few snippets of how we used the Deque to our benefit:
> This is how we instantiated the two Deque's required one each for Undo and Redo.
>
> <img width="302" alt="screen shot 2016-11-22 at 12 16 31 am" src="https://media.github.umn.edu/user/5701/files/281a3a56-b049-11e6-893d-93297cc716bf">

> The Undo function looks something like this as shown in the snippet below, where we push the copy of the current canvas made by temp, to the back of the Deque, and if the Deque size goes above 50 then we can simply pop from the front of the Deque and then push from the back, staying within our limit of 50 Undo's.

> <img width="853" alt="screen shot 2016-11-22 at 12 19 45 am" src="https://media.github.umn.edu/user/5701/files/6a19f9f0-b049-11e6-8e2e-c6c800cecabd">

> Here is how the Redo function looks like, so it simply pushes the changed canvas on the redo Deque, and each time we press Redo, all it does is pop from the back of the Deque, and set that to the current PixelBuffer.

> <img width="555" alt="screen shot 2016-11-22 at 12 22 53 am" src="https://media.github.umn.edu/user/5701/files/dde57116-b049-11e6-84a1-4cef29646235">

> Just to get the initial instance of the PixelBuffer we have a ReceivePixelBuffer method, which is described as shown below:
>
> <img width="598" alt="screen shot 2016-11-22 at 12 23 49 am" src="https://media.github.umn.edu/user/5701/files/f7d24072-b049-11e6-8ef3-86f695e0713c">

### 2.2 Design Justification

> In this case the first thought that had come to mind was to use a stack, which made complete sense because we could push onto the Undo stack, pop from it when needed and so with the Redo stack. But the problem with this design decision was that we have a limit of 50 undo's, now once we reached 50 undo's what does the stack do? We still want the recent 49 Undo instances and add the latest 50th one each time it happens. However a stack doesn't support that kind of an operation exactly.

> To overcome this dificulty, we decided to use a Deque instead, this helped us solve the problem of having at most 50 Undo's because apparently Deque comes with the functionality of pushing and popping that can happen on either ends. So each time an Undo is pressed, a copy of the original canvas is saved and pushed to the back of Undo, and each time we press Redo, the changed instance is popped from the Redo Deque again. So as compared to a Stack, a Deque gave us much more functionalilty and flexibility with more operations.

> The way we store changes runs relatively quickly, and doesn't take up to much space in the source code, however it uses up a large amount of data. An alternative way to store undo's, and redo's, would be to only store the change that was made to display_buffer_. Doing so would use much less data, however, it would take longer to calculate. It would also have taken much longer to implement. We decided to have the deques store entire PixelBuffers, because the machines that will be running FlashPhoto will have plenty of room to store them, and, also, because we decided that there were better uses of our limited time than implementing a way to only record the changes.

> We categorized changes as single brush strokes, (ie, one click, then release of the mouse), and applications of filters, as it was the most intuitive to the user. To have undo only remove a single application of a tool's mask would not feel satisfying to the user, and would make it much more difficult to get any use out of the undo functionality. Loading another image is a special case, because it clears both deques, and pushes nothing into either. As a group, we decided that it would feel more natural to have loading a new image be equivilent to closing, and starting up FlashPhoto, compared to being able to undo loading an image.

## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.

#### Step 1
>
> To add a filter we simply create an invert.h file with the ApplyFilter and ModifyPixel as shown below:
>
> <img width="735" alt="screen shot 2016-11-22 at 1 06 34 am" src="https://media.github.umn.edu/user/5701/files/f140e776-b04f-11e6-8fbc-206e90b5d9b7">
>
#### Step 2
>
> Then we add an invert.cc file with the desired description of the colors, and link it to our code. Here is a snippet of the .cc file:
>
> <img width="649" alt="screen shot 2016-11-22 at 12 59 35 am" src="https://media.github.umn.edu/user/5701/files/72744e10-b04f-11e6-9af2-e176d772b06c">

### Programming Tutorial: Adding a New Pencil Tool to FlashPhoto

> Step 1: Here is how our design choice of having all tools as individual children of the Parent Tool would come into play as adding another tool would be simply adding a new sub-class, and linking it to Brushwork_app, as we have done with the other tools.
So how do we go about it? Well, here is how we would start off, as the other tools, Pencil would have its own overloaded SetMask and will inherit from Tool. Here is a snippet of what that would look like in pencil.h

> <img width="610" alt="screen shot 2016-10-20 at 12 44 21 am" src="https://media.github.umn.edu/user/5701/files/acce6b0e-965f-11e6-94f0-9f19cc721dc1">

> Step 2: Next we would move onto creating a mask for our new tool, so it works as described, that is like the pen and calligraphy, but with just 1 pixel in all, so clearly its mask is just 1 pixel here, and thats what the code snippet below shows:

> <img width="630" alt="screen shot 2016-10-20 at 1 15 08 am" src="https://media.github.umn.edu/user/5701/files/bcceed8c-9662-11e6-9c1b-d0f47174a285">

> Step 3: Next we would need to link this pencil tool, with the FlashPhoto so its functional just like we have done with the other tools, i.e. include it in the dependencies list of the FlashPhoto as the snippet below illustrates:

> <img width="347" alt="screen shot 2016-11-22 at 1 13 58 am" src="https://media.github.umn.edu/user/5701/files/fd744622-b050-11e6-96ac-9a921d6eacb4">

> Step 4: We would also need to add our new tool to the InitTools in FlashPhoto so that the tool can be initialized and in InitGlui so that it's interface can be created as well. The snippet below explains that part:

> <img width="539" alt="screen shot 2016-11-22 at 1 15 13 am" src="https://media.github.umn.edu/user/5701/files/278ea092-b051-11e6-8be5-bf3687e654d8">

> Here is the InitGlui portion that would need an addition as well:

> <img width="616" alt="screen shot 2016-11-22 at 1 15 52 am" src="https://media.github.umn.edu/user/5701/files/3f6d38ea-b051-11e6-8cca-72e2da6ab6af">

> Finally, run make from inside the /project/intertion2/ directory, this will compile the new tool and link the object files with the others, generating a new .exe that has our new working pencil tool.
