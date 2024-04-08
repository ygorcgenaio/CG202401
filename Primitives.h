#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cstddef>
#include <array>
#include <vector>

template<class Prims, class Cont>
auto assemble(const Prims& P, const Cont& V)
{
	using Primitive = decltype(P.assemble(0, std::data(V)));
	std::vector<Primitive> res(P.size());
	for(unsigned int i = 0; i < P.size(); i++)
		res[i] = P.assemble(i, std::data(V));
	return res;
}

///////////////////////////////////////////////////////////////////////
template<class V>
using Line = std::array<V, 2>;

class Lines{
	size_t n;
	public:
	Lines(size_t n_verts){ n = n_verts/2; }

	size_t size() const{ return n; }

	template<typename Vertex>
	Line<Vertex> assemble(unsigned int i, const Vertex* V) const{
		return { V[2*i], V[2*i+1] };
	}
};

class LineStrip{
	/*****************************/
	/* TAREFA: AULA 06 */
	/*****************************/
};

class LineLoop{
	/*****************************/
	/* TAREFA: AULA 06 */
	/*****************************/
};

///////////////////////////////////////////////////////////////////////
template<class V>
using Triangle = std::array<V, 3>;

class Triangles{
	size_t n;
	public:
	Triangles(size_t s){ n = s/3; }

	size_t size() const{ return n; }

	template<typename Vertex>
	Triangle<Vertex> assemble(unsigned int i, const Vertex* V) const{
		return { V[3*i], V[3*i + 1], V[3*i + 2] };
	}
};

class TriangleStrip{
	/*****************************/
	/* TAREFA: AULA 06 */
	/*****************************/
};

class TriangleFan{
	/*****************************/
	/* TAREFA: AULA 06 */
	/*****************************/
};

class TrianglesRange{
	unsigned int first;
	unsigned int n;
	public:
	TrianglesRange(unsigned int first, unsigned int s): first{first}, n{s/3}{}

	size_t size() const{ return n; }

	template<typename Vertex>
	Triangle<Vertex> assemble(unsigned int i, const Vertex* V) const{
		return { V[first + 3*i], V[first + 3*i + 1], V[first + 3*i + 2] };
	}
};

///////////////////////////////////////////////////////////////////////
template<class Primitives>
class Elements{
	const unsigned int* indices;
	Primitives P;
	
	public:
	template<class Indices>
	Elements(const Indices& in): indices{std::data(in)}, P{std::size(in)}{}

	size_t size() const{ return P.size(); }

	template<typename Vertex>
	auto assemble(unsigned int i, const Vertex* V) const{
		return assemble(P.assemble(i, indices), V);
	}
	
	template<typename Vertex>
	Line<Vertex> assemble(Line<unsigned int> indices, const Vertex* V) const{
		return { V[indices[0]], V[indices[1]] };
	}
	
	template<typename Vertex>
	Triangle<Vertex> assemble(Triangle<unsigned int> indices, const Vertex* V) const{
		return { V[indices[0]], V[indices[1]], V[indices[2]] };
	}
};

///////////////////////////////////////////////////////////////////////
template<class Primitives>
class TriLines{
	Primitives P;
	public:

	template<class... Args>
	TriLines(Args&&... args) : P{std::forward<Args>(args)...}{}

	size_t size() const{ return 3*P.size(); }

	template<typename Vertex>
	Line<Vertex> assemble(unsigned int i, const Vertex* V) const{
		unsigned j = i/3;
		unsigned k = i%3;

		Triangle<Vertex> tri = P.assemble(j, V);

		return { tri[k], tri[(k+1)%3] };
	}
};

#endif
