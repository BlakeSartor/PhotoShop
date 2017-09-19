# Design Justifications for BrushWork
#### Group Name:
Group C-10

#### Members:
- Blake Sartor
- Zechariah Nelson
- Raghav Mutneja

#### Instructions 
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.


## 1  Design Question One
> This iteration of the project is all about tools. Naturally, a key design decision is how these tools are represented. Each tool has several characteristics, including the shape of the tool, its size, and the way it blends with the canvas when the tool is applied. Some tools share characteristics with other tools, such as how the pen and calligraphy pen tools blend with the canvas in the same manner. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description

> So we had to begin by thinking about how to put all the different tools together to work on the same canvas, with each other for instance once I use the pen, and then the highlighter, then the highlighter should work over the pen and be a little transparent and so on. So we decided to treat all the tools as children of the Parent class 'Tool'. This is somewhat similar to how a Mallard Duck or a RedHead is still a "Duck". This gave us the benefit that now the Parent Tool class includes Mask, Pixel-buffer and Color-data instead of each tool having to do it individually. Just like all the Duck had common features such as quack/fly, we have the tools with the common feature that they all have a mask, which can be overloaded as each tool has a different mask. So our uml would look like this (i.e. how our design affected the relations of the classes given to us)

> ![uml](https://media.github.umn.edu/user/5701/files/8d305ca2-96c4-11e6-9e64-fc771753e663)

> The Mask class has a two dimensional array of floats, used for the opacity values, and height and width attributes. The constructors for Mask allocate data for an array of the appropriate size, however, it does not set them to any values, so any time a new Mask object is created, it must be immediately followed by nested for loops that set the opacity values. Mask has no important functions other than getters, and setters. This can be seen in the code snippet below:
<img width="446" alt="screen shot 2016-10-19 at 10 50 59 pm" src="https://media.github.umn.edu/user/5701/files/9de0ccf6-964e-11e6-9078-fdd220c2c2ad">

> For our Tool (parent class) the key attribute is mask_ which is a Mask object, that has the opacity values for every pixel in the Tool's mask. The key functions were SetMask() and ApplyMask(int mouse_x,int mouse_y,PixelBuffer *canvas,ColorData *activeColor). SetMask() sets mask_ to a new Mask object, then sets the opacity values for every element in the array. SetMask() must be overwritten in each child of Tool. ApplyMask takes in the position of the mouse, the canvas, and a ColorData object as arguments. It adds the color in activeColor, to all of the pixels in canvas, that overlap with the pixels in mask_, weighted by the opacity value in that pixel of mask_. Given below is a snippet of how our Tool is using these attributes:
<img width="704" alt="screen shot 2016-10-19 at 10 56 27 pm" src="https://media.github.umn.edu/user/5701/files/53b2992e-964f-11e6-8f20-c7d23134bf86">

> Now what our tools do is that they each overload their own SetMask, and create their own masks. This was pretty straightforward for most except highlighter and the spray-can, which had a transparency and a linear fall off respectively.
Below you can see our highlighter, how it overloads its SetMask and how it goes about the transparency of 40% of its own color. The Highlighter class also has global_mask_ as a member variable. global_mask_ is a mask with the same dimensions as the canvas, that stores whether or not a pixel at a given point has been changed recently. Highlighter also overwrites ApplyMask, such that it uses another member function, RecentlyDrawn(pixel_x, pixel_y,PixelBuffer *canvas) to check if the pixel it is about to modify has recently been modified by the highlighter. If it has, highlighter does not draw on that pixel.
<img width="602" alt="screen shot 2016-10-19 at 11 01 30 pm" src="https://media.github.umn.edu/user/5701/files/19a6cdbc-9650-11e6-882a-a2329dbd0aa0">
> ********************************************************************************************
<img width="657" alt="screen shot 2016-10-19 at 11 02 07 pm" src="https://media.github.umn.edu/user/5701/files/23024a80-9650-11e6-9577-ca061bb0ef75">

> Now moving on to the Spray-can which had a mask with a linear fall off wasn't quite straightforward either, below is a snippet of how we got to the circular mask with a linear fall off:
<img width="754" alt="screen shot 2016-10-19 at 11 05 47 pm" src="https://media.github.umn.edu/user/5701/files/a7096c8c-9650-11e6-9456-75cb719cfea0">

> For the rest of the tools, its a simple overload of the SetMask as shown below:
<img width="590" alt="screen shot 2016-10-19 at 11 08 11 pm" src="https://media.github.umn.edu/user/5701/files/f422a3a8-9650-11e6-9fb2-7e5dcb777994">

> The next problem we had to face was the interpolation which basically dealt with the fact that if we moved the mouse too fast, we wouldn't get a smooth interaction on the canvas but a broken one because the calulations take a little longer, so to avoid that this is how interpolation helped us deal with every portion of the canvas individually as shown below:

> <img width="620" alt="screen shot 2016-10-19 at 11 11 25 pm" src="https://media.github.umn.edu/user/5701/files/66c8b3de-9651-11e6-8133-2a68b00fda1d">

### 1.2 Design Justification
> We implimented masks as a class, instead of only a two dimensional array of floats. Each tool has one Mask object (or two, in the case of highlighter) instead of having a reference to a reference of floats as attributes. Our main motivation for doing this was for future proofing a later date in which we might be required to impliment changable sizes for Tools. Creating a new Mask object with a constructor is easier, and takes up fewer lines than deallocating an array, than allocating new arrays of different sizes. It also allows tool classes to be simpler, as the width and height of the mask can be kept in Mask, as opposed to being kept in Tool. When accessing individual pixels, checking out of bounds can be done in the Mask, instead of the Tool. Again, this would keep functions in Tool shorter, and easier to read, without adding too many functions to Tool.

> The function for actually applying the mask the pixels on the canvas belongs to the Tool class. It takes the mouse position, the canvas to modify, and the color to modify it with as arguments. We made this decision because it allows us to switch between tools, without adding any additional code, or special cases to the BrushworkApp class. It also allows Tools that require unique applications of their masks, (such as the eraser tool, which uses the background color instead of the active color), to do so, by overwriting the virtual function. The function needs to take the mouse position as arugments, as it needs to know what position to apply the mask at, it must take the PixelBuffer object as an argument, because it needs access to the pixels it needs to modify, and, it needs a ColorData object as an argument, because it needs to know what color to add. Eraser does not use the final argument, as it uses the background color instead, however, the final argument was left in, so that the function could be used interchangeably with the parent class's ApplyMask() function. It has access to the background color, because it has access to the PixelBuffer object, which contains the background color. 

> The SetMask function was used to allocate memory to the mask, and to set it's values, because it will make it easier in the future to have masks of different sizes, or opacities, by overloading SetMask to work with different arguments. This will save space in other functions, and make them easier to read. For example, pen might have a SetMask function with one argument, that it uses as the diameter of the mask, and, SprayCan might have a SetMask function that takes arguments both for size, and opacity at the center of the mask.

> Each individual tool will be it's own child class, that inherits from the pure virtual Tool class. This will cause more classes, and has the potential to cause a bit of a class explosion, however, it will also make each individual class cleaner. The class explosion issue will only become serious if a large number of tools are required. Because each Tool has a mask, that can easily be changed to different sizes, and opacities, these minor changes will not require a new Tool object to be created, or a new class to be defined. Based on the types of tools, and masks that we expect to be required in later iterations, we thought that having each tool be a class, and having each class capable of easily changing it's mask and dimensions would be a good compromise between number of classes, and class complexity.

## 2  Design Question Two
> Unlike most of the tools, the Eraser returns the canvas to its original color. One of the challenges in this iteration is giving the eraser the authority or information required to have this effect while having minimal impact on the way the rest of the tools are defined. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description
> Our solution was having eraser overload the function ApplyMask, which draws on the canvas. As ApplyMask already took a PixelBuffer as an argument, it already had access to the background color.  All we needed to do was to replace activeColor, which was passed as an argument, with canvas->background_color() . Unfortunately, the ColorData passed as an argument is completely unused in PixelBuffer's ApplyMask function, but, it must keep it as an argument, so that it can overwrite the parent class's version of ApplyMask, and be used in place of it. Having arguments that you don't use, for the sake of overwriting a function is not that big of an issue though.

> The ApplyMask function already took the PixelBuffer object as an argument, because ApplyMask is the function that actuall modifies the canvas in our implimentation. It is called in the MouseDragged events in BrushworkApp, at each step of interpoalation.

### 2.2 Design Justification
> We implimented this solution because our ApplyMask function already took the canvas as an argument. ApplyMask already had access to the background color, indirectly, because it had a reference to PixelBuffer. This solution allows all different types of tools to be used interchangeably in the mouse events of BrushworkApp, keeps the calls in those events clean, and simple, and allows for special cases, like the eraser tool, and, potentially more special cases that appear in later iterations.

## 3  Design Question Three
> A new developer on your team must add a new tool to BrushWork. This tool is called  _Pencil._ This tool is a single, non-transparent pixel that completely replaces the existing colors on the canvas in the same way as the pen or calligraphy pen blend.  
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new tool.

### Programming Tutorial: Adding a New Pencil Tool to BrushWork

> Step 1: Here is how our design choice of having all tools as individual children of the Parent Tool would come into play as adding another tool would be simply adding a new sub-class, and linking it to Brushwork_app, as we have done with the other tools.
So how do we go about it? Well, here is how we would start off, as the other tools, Pencil would have its own overloaded SetMask and will inherit from Tool. Here is a snippet of what that would look like in pencil.h

> <img width="610" alt="screen shot 2016-10-20 at 12 44 21 am" src="https://media.github.umn.edu/user/5701/files/acce6b0e-965f-11e6-94f0-9f19cc721dc1">

> Step 2: Next we would move onto creating a mask for our new tool, so it works as described, that is like the pen and calligraphy, but with just 1 pixel in all, so clearly its mask is just 1 pixel here, and thats what the code snippet below shows:

> <img width="630" alt="screen shot 2016-10-20 at 1 15 08 am" src="https://media.github.umn.edu/user/5701/files/bcceed8c-9662-11e6-9c1b-d0f47174a285">

> Step 3: Next we would need to link this pencil tool, with the Brushwork-app so its functional just like we have done with the other tools, i.e. include it in the dependencies list of the Brushwork-app as the snippet below illustrates:

> <img width="660" alt="screen shot 2016-10-20 at 1 07 29 am" src="https://media.github.umn.edu/user/5701/files/abd73eae-9661-11e6-8c40-c2e7b6a3de8d">

> Step 4: We would also need to add our new tool to the InitTools in Brushwork-app so that the tool can be initialized and in InitGlui so that it's interface can be created as well. The snippet below explains that part:

> <img width="545" alt="screen shot 2016-10-20 at 1 00 20 am" src="https://media.github.umn.edu/user/5701/files/b4f401da-9660-11e6-84e0-b331d68dd619">

> Here is the InitGlui portion that would need an addition as well:

> <img width="613" alt="screen shot 2016-10-20 at 1 00 54 am" src="https://media.github.umn.edu/user/5701/files/cf017f94-9660-11e6-8fd9-8dd2268069c0">

> Step 5: We must now include our new tool inside our makefile, so when running make, it will compile and link our new class.

> <img width="418" alt="screen shot 2016-10-20 at 10 34 10 am" src="https://media.github.umn.edu/user/2666/files/2bd05130-96b3-11e6-8767-6c0b85c9f562">

> As we can see from the above screenshot, we have added pencil.o to our list of object files that our makefile will generate based on depencies.

> Finally, run make from inside the /project/intertion1/ directory, this will compile the new tool and link the object files with the others, generating a new .exe that has our new working pencil tool.

