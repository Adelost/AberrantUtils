#pragma once

namespace ae
{
	/**	Randomization utility class. */
	class Random
	{
	public:
		/** Sets an arbitrary random seed which will be used to generate
			randomized values. */
		static void initSeed();
		/** Specifies the "seed" randomized values will be generated from. Identical
			seeds will generate an identical succession of numbers. */
		static void setSeed(int seed);
		/** Returns a randomized "int" between the values min and max. */
		static int next(int min, int max);
		/** Returns a randomized "int" between 0 and less than max. */
		static int nextUniform(int max);
		/** Returns a randomized "float" between 0.0f and 1.0f. */
		static float nextFloat();
		/** Returns a randomized "float" between min and max. */
		static float nextFloat(float min, float max);
	};
}
