#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
	namespace impl {

		template<typename Iter>
		class range_enumerator;

		template<typename T>
		class take_enumerator;

		template<typename T>
		class drop_enumerator;

		template<typename T, typename U, typename F>
		class select_enumerator;

		template<typename T, typename F>
		class until_enumerator;

		template<typename T, typename F>
		class where_enumerator;

		template<typename T>
		class enumerator {
		public:
			enumerator(const enumerator&) = delete;
			enumerator& operator=(const enumerator&) = delete;
			enumerator& operator=(enumerator&&) = delete;
			enumerator(enumerator&&) noexcept = default;
			enumerator() = default;
			virtual ~enumerator() = default;

			virtual T& operator*() = 0; // Получает текущий элемент.
			virtual enumerator &operator++() = 0;  // Переход к следующему элементу
			virtual operator bool() const = 0;  // Возвращает true, если есть текущий элемент

			auto take(int count) {
				return take_enumerator<T>(*this, count);
			}

			auto drop(int count) {
				return drop_enumerator<T>(*this, count);
			}

			template<typename U = T, typename F>
			auto select(const F& func) {
				return select_enumerator<U, T, F>(*this, func);
			}

			template<typename F>
			auto until(const F& func) {
				return until_enumerator<T, F>(*this, func);
			}

			auto until_eq(T value) {
				return until([value](const T& el) { return el == value; });
			}

			template<typename F>
			auto where(const F& func) {
				return where_enumerator<T, F>(*this, func);
			}

			auto where_neq(T value) {
				return where([value](T& el) { return el != value; });
			}

			std::vector<T> to_vector() {
				enumerator &self = *this;
				std::vector<T> res;
				while (self) {
					res.push_back(*self);
					++self;
				}
				return res;
			}

			template<typename Iter>
			void copy_to(Iter it) {
				enumerator &self = *this;
				while (self) {
					*it = *self;
					++self;
					++it;
				}
			}
		};

		template<typename Iter>
		class range_enumerator : public enumerator<typename std::iterator_traits<Iter>::value_type> {
		public:
			using T = typename std::iterator_traits<Iter>::value_type;

			range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {
				if(begin_ != end_)
					created_element = *begin_;
			}

			virtual operator bool() const {
				return begin_ != end_;
			}

			virtual T& operator*() {
				return created_element;
			}

			virtual enumerator<T> &operator++() {
				if (begin_ != end_) {
					++begin_;
					created_element = *begin_;
				}
				return *this;
			}
		private:
			T created_element;
			Iter begin_, end_;
		};

		template<typename T>
		class take_enumerator : public enumerator<T> {
		public:
			take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

			virtual operator bool() const {
				return parent_ && count_;
			}

			virtual T& operator*() {
				return *parent_;
			}

			virtual enumerator<T>& operator++() {
				--count_;
				if (count_)
					++parent_;
				return *this;
			}
		private:
			enumerator<T> &parent_;
			int count_;
		};

		template<typename T>
		class drop_enumerator : public enumerator<T> {
		public:
			drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
				while (*this && count) {
					++parent_;
					--count;
				}
			}

			virtual operator bool() const {
				return parent_;
			}

			virtual T& operator*() {
				return *parent_;
			}

			virtual enumerator<T>& operator++() {
				++parent_;
				return *this;
			}
		private:
			enumerator<T> &parent_;
		};

		template<typename T, typename U, typename F>
		class select_enumerator : public enumerator<T> {
		public:
			select_enumerator(enumerator<U> &parent, const F& func) : parent_(parent), func_(func) {
				created_element = func_(*parent_);
			}

			virtual operator bool() const {
				return parent_;
			}

			virtual T& operator*() {
				return created_element;
			}

			virtual enumerator<T>& operator++() {
				++parent_;
				created_element = func_(*parent_);
				return *this;
			}
		private:
			T created_element;
			enumerator<U> &parent_;
			F func_;
		};

		template<typename T, typename F>
		class until_enumerator : public enumerator<T> {
		public:
			until_enumerator(enumerator<T> &parent, const F& predicate) : parent_(parent), predicate_(predicate) {}

			virtual operator bool() const {
				return parent_ && !predicate_(*parent_);
			}

			virtual T& operator*() {
				return *parent_;
			}

			virtual enumerator<T>& operator++() {
				++parent_;
				return *this;
			}
		private:
			enumerator<T> &parent_;
			F predicate_;
		};

		template<typename T, typename F>
		class where_enumerator : public enumerator<T> {
		public:
			where_enumerator(enumerator<T> &parent, const F& func) : parent_(parent), func_(func) {
				while (*this && !func_(*parent_))
					++parent_;
			}

			virtual operator bool() const {
				return parent_;
			}

			virtual T& operator*() {
				return *parent_;
			}

			virtual enumerator<T>& operator++() {
				do {
					++parent_;
				} while (*this && !func_(*parent_));
				return *this;
			}
		private:
			enumerator<T> &parent_;
			F func_;
		};
	} // namespace impl

	template<typename T>
	auto from(T begin, T end) {
		return impl::range_enumerator<T>(begin, end);
	}
} // namespace linq

#endif

