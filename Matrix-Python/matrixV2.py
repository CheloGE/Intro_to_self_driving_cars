def zeroes(height, width):
    """This function returns a matrix full of zeroes based on the size introduced"""
    zeroM = [[0.0 for _ in range(width)] for _ in range(height)]
    return Matrix(zeroM)

def identity(size):
    """This function returns an identity matrix based on the size introduced"""
    eye = zeroes(size,size)
    for i in range(size):
        eye.m[i][i]=1.0
    return eye
class Matrix(object):
    
    def __init__(self,mat):
        """constructor function"""
        self.h = len(mat)
        self.w = len(mat[0])
        self.m = mat
    def __repr__(self):
        """this function defines what the class does when called by print"""
        disp = ""
        for row in self.m:
            disp += " ".join([str(val)+" " for val in row])
            disp += "\n"
        return disp

    def __add__(self, other):
        """this function defines the behaviour when doing addition. i.e. objectA + objectB"""
        
        """ Note that in this special functions always the other is the object or value 
            on the left. i.e. other=objectA and self=objectB"""
        if self.h != other.h or self.w != other.w:
            raise(ValueError,"matrices must be of same size to be added")
        else:
            
            added_M = [[self.m[i][j]+other.m[i][j] for j in range(self.w)] for i in range(self.h)]
            
            return Matrix(added_M)
    