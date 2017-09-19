Prelab:

If we restrict the size of the Gaussian kernels to odd integers, the size of the largest padded image to handle padding will be 266x266. The top left index should be (N/2,N/2), while the bottom right index should be (266-N/2, 266-N/2)

Gaussian Kernels:

Raw:

0.7788	0.8825	0.7788
0.8825	1.0000	0.8825
0.7788	0.8825	0.7788

Normalized:

0.1019	0.1154	0.1019
0.1154	0.1308	0.1154	
0.1019	0.1154	0.1019

Experimentation:

1)
	N constant,sigma vary (Using N=5, where sigma = 0.5, 2.0,3.0,4.0,40.0)
		As sigma increases, blur increases. As sigma decreases, the blur decreases.  
	N vary, sigma constant (Using N = 5, 7, 9, 11, where sigma = 2.0 )
		The brightness is noticibly decreased as N increases.
2) The sobel filter appears to highlight and emphasize edges. 

3) The reason we do not get the same image back by Unsharpening an already blurred-Image is because by blurring the image, we lose a certain amount of pixels. These pixels are lost, and unsharpening will not bring them back. 

Number of Calculations as N grows:
	Since the image remains consant, the number of calculations made can be described as: kn^2 where k is the constant image, and n is the size of the kernel. In Big O notation, this would be O(n^2)