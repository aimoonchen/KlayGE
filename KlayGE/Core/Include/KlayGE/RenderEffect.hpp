// RenderEffect.hpp
// KlayGE 渲染效果脚本类 头文件
// Ver 3.11.0
// 版权所有(C) 龚敏敏, 2003-2010
// Homepage: http://www.klayge.org
//
// 3.11.0
// Add RenderTechnique::Transparent() (2010.9.12)
//
// 3.9.0
// 直接从fxml文件读取特效脚本 (2009.4.21)
//
// 3.8.0
// 支持CBuffer (2008.10.6)
//
// 3.6.0
// 增加了Clone (2007.6.11)
//
// 3.5.0
// 改用基于xml的特效格式 (2006.10.21)
//
// 3.4.0
// 重写了parameter的存储结构 (2006.9.15)
//
// 3.2.0
// 支持了bool类型 (2006.3.8)
//
// 3.0.0
// 增加了RenderTechnique和RenderPass (2005.9.4)
//
// 2.8.0
// 增加了Do*函数，使用模板方法模式 (2005.7.24)
// 使用新的自动更新参数的方法 (2005.7.25)
//
// 2.5.0
// 去掉了Clone (2005.4.16)
// SetTechnique的返回类型改为bool (2005.4.25)
//
// 2.1.2
// 增加了Parameter (2004.5.26)
//
// 2.0.3
// 修改了SetTexture的参数 (2004.3.6)
// 增加了SetMatrixArray/GetMatrixArray (2004.3.11)
//
// 2.0.0
// 初次建立 (2003.8.15)
//
// 修改记录
//////////////////////////////////////////////////////////////////////////////////

#ifndef _RENDEREFFECT_HPP
#define _RENDEREFFECT_HPP

#pragma once

#ifndef KLAYGE_CORE_SOURCE
#define KLAYGE_LIB_NAME KlayGE_Core
#include <KlayGE/config/auto_link.hpp>
#endif

#include <KlayGE/PreDeclare.hpp>
#include <vector>
#include <string>
#include <algorithm>

#include <boost/noncopyable.hpp>
#include <boost/tuple/tuple.hpp>

#include <KlayGE/RenderEngine.hpp>
#include <KlayGE/Texture.hpp>
#include <KlayGE/ShaderObject.hpp>
#include <KlayGE/Math.hpp>

namespace KlayGE
{
	enum RenderEffectDataType
	{
		REDT_bool = 0,
		REDT_string,
		REDT_texture1D,
		REDT_texture2D,
		REDT_texture3D,
		REDT_textureCUBE,
		REDT_texture1DArray,
		REDT_texture2DArray,
		REDT_texture3DArray,
		REDT_textureCUBEArray,
		REDT_sampler,
		REDT_shader,
		REDT_uint,
		REDT_uint2,
		REDT_uint3,
		REDT_uint4,
		REDT_int,
		REDT_int2,
		REDT_int3,
		REDT_int4,
		REDT_float,
		REDT_float2,
		REDT_float2x2,
		REDT_float2x3,
		REDT_float2x4,
		REDT_float3,
		REDT_float3x2,
		REDT_float3x3,
		REDT_float3x4,
		REDT_float4,
		REDT_float4x2,
		REDT_float4x3,
		REDT_float4x4,
		REDT_buffer,
		REDT_structured_buffer,
		REDT_byte_address_buffer,
		REDT_rw_buffer,
		REDT_rw_structured_buffer,
		REDT_rw_texture1D,
		REDT_rw_texture2D,
		REDT_rw_texture3D,
		REDT_rw_texture1DArray,
		REDT_rw_texture2DArray,
		REDT_rw_byte_address_buffer,
		REDT_append_structured_buffer,
		REDT_consume_structured_buffer
	};

	class KLAYGE_CORE_API RenderVariable
	{
	public:
		RenderVariable();
		virtual ~RenderVariable() = 0;

		virtual RenderVariablePtr Clone() = 0;

		virtual RenderVariable& operator=(bool const & value);
		virtual RenderVariable& operator=(uint32_t const & value);
		virtual RenderVariable& operator=(int32_t const & value);
		virtual RenderVariable& operator=(float const & value);
		virtual RenderVariable& operator=(uint2 const & value);
		virtual RenderVariable& operator=(uint3 const & value);
		virtual RenderVariable& operator=(uint4 const & value);
		virtual RenderVariable& operator=(int2 const & value);
		virtual RenderVariable& operator=(int3 const & value);
		virtual RenderVariable& operator=(int4 const & value);
		virtual RenderVariable& operator=(float2 const & value);
		virtual RenderVariable& operator=(float3 const & value);
		virtual RenderVariable& operator=(float4 const & value);
		virtual RenderVariable& operator=(float4x4 const & value);
		virtual RenderVariable& operator=(TexturePtr const & value);
		virtual RenderVariable& operator=(boost::tuple<TexturePtr, uint32_t, uint32_t, uint32_t, uint32_t> const & value);
		virtual RenderVariable& operator=(SamplerStateObjectPtr const & value);
		virtual RenderVariable& operator=(GraphicsBufferPtr const & value);
		virtual RenderVariable& operator=(std::string const & value);
		virtual RenderVariable& operator=(shader_desc const & value);
		virtual RenderVariable& operator=(std::vector<bool> const & value);
		virtual RenderVariable& operator=(std::vector<uint32_t> const & value);
		virtual RenderVariable& operator=(std::vector<int32_t> const & value);
		virtual RenderVariable& operator=(std::vector<float> const & value);
		virtual RenderVariable& operator=(std::vector<uint2> const & value);
		virtual RenderVariable& operator=(std::vector<uint3> const & value);
		virtual RenderVariable& operator=(std::vector<uint4> const & value);
		virtual RenderVariable& operator=(std::vector<int2> const & value);
		virtual RenderVariable& operator=(std::vector<int3> const & value);
		virtual RenderVariable& operator=(std::vector<int4> const & value);
		virtual RenderVariable& operator=(std::vector<float2> const & value);
		virtual RenderVariable& operator=(std::vector<float3> const & value);
		virtual RenderVariable& operator=(std::vector<float4> const & value);
		virtual RenderVariable& operator=(std::vector<float4x4> const & value);

		virtual void Value(bool& val) const;
		virtual void Value(uint32_t& val) const;
		virtual void Value(int32_t& val) const;
		virtual void Value(float& val) const;
		virtual void Value(uint2& val) const;
		virtual void Value(uint3& val) const;
		virtual void Value(uint4& val) const;
		virtual void Value(int2& val) const;
		virtual void Value(int3& val) const;
		virtual void Value(int4& val) const;
		virtual void Value(float2& val) const;
		virtual void Value(float3& val) const;
		virtual void Value(float4& val) const;
		virtual void Value(float4x4& val) const;
		virtual void Value(TexturePtr& val) const;
		virtual void Value(boost::tuple<TexturePtr, uint32_t, uint32_t, uint32_t, uint32_t>& val) const;
		virtual void Value(SamplerStateObjectPtr& val) const;
		virtual void Value(GraphicsBufferPtr& value) const;
		virtual void Value(std::string& val) const;
		virtual void Value(shader_desc& val) const;
		virtual void Value(std::vector<bool>& val) const;
		virtual void Value(std::vector<uint32_t>& val) const;
		virtual void Value(std::vector<int32_t>& val) const;
		virtual void Value(std::vector<float>& val) const;
		virtual void Value(std::vector<uint2>& val) const;
		virtual void Value(std::vector<uint3>& val) const;
		virtual void Value(std::vector<uint4>& val) const;
		virtual void Value(std::vector<int2>& val) const;
		virtual void Value(std::vector<int3>& val) const;
		virtual void Value(std::vector<int4>& val) const;
		virtual void Value(std::vector<float2>& val) const;
		virtual void Value(std::vector<float3>& val) const;
		virtual void Value(std::vector<float4>& val) const;
		virtual void Value(std::vector<float4x4>& val) const;
	};

	template <typename T>
	class RenderVariableConcrete : public RenderVariable
	{
	public:
		RenderVariablePtr Clone()
		{
			RenderVariablePtr ret = MakeSharedPtr<RenderVariableConcrete<T> >();
			T val;
			this->Value(val);
			*ret = val;
			return ret;
		}

		RenderVariable& operator=(T const & value)
		{
			val_ = value;
			return *this;
		}

		void Value(T& val) const
		{
			val = val_;
		}

	protected:
		T val_;
	};

	class RenderVariableTexture : public RenderVariable
	{
	public:
		RenderVariablePtr Clone()
		{
			RenderVariablePtr ret = MakeSharedPtr<RenderVariableTexture>();
			TexturePtr val;
			this->Value(val);
			*ret = val;
			std::string elem_type;
			this->Value(elem_type);
			*ret = elem_type;
			return ret;
		}

		RenderVariable& operator=(TexturePtr const & value)
		{
			uint32_t array_size = 0;
			uint32_t mipmap = 0;
			if (value)
			{
				array_size = value->ArraySize();
				mipmap = value->NumMipMaps();
			}
			return this->operator=(boost::make_tuple(value, 0, array_size, 0, mipmap));
		}

		RenderVariable& operator=(boost::tuple<TexturePtr, uint32_t, uint32_t, uint32_t, uint32_t> const & value)
		{
			val_ = value.get<0>();
			first_array_index_ = value.get<1>();
			num_items_ = value.get<2>();
			first_level_ = value.get<3>();
			num_levels_ = value.get<4>();
			return *this;
		}

		void Value(TexturePtr& val) const
		{
			val = val_;
		}

		void Value(boost::tuple<TexturePtr, uint32_t, uint32_t, uint32_t, uint32_t>& val) const
		{
			val = boost::make_tuple(val_, first_array_index_, num_items_, first_level_, num_levels_);
		}

		RenderVariable& operator=(std::string const & value)
		{
			elem_type_ = value;
			return *this;
		}

		void Value(std::string& val) const
		{
			val = elem_type_;
		}

	protected:
		TexturePtr val_;
		uint32_t first_array_index_;
		uint32_t num_items_;
		uint32_t first_level_;
		uint32_t num_levels_;
		std::string elem_type_;
	};

	class RenderVariableBuffer : public RenderVariable
	{
	public:
		RenderVariablePtr Clone()
		{
			RenderVariablePtr ret = MakeSharedPtr<RenderVariableBuffer>();
			GraphicsBufferPtr val;
			this->Value(val);
			*ret = val;
			std::string elem_type;
			this->Value(elem_type);
			*ret = elem_type;
			return ret;
		}

		RenderVariable& operator=(GraphicsBufferPtr const & value)
		{
			val_ = value;
			return *this;
		}

		void Value(GraphicsBufferPtr& val) const
		{
			val = val_;
		}

		RenderVariable& operator=(std::string const & value)
		{
			elem_type_ = value;
			return *this;
		}

		void Value(std::string& val) const
		{
			val = elem_type_;
		}

	protected:
		GraphicsBufferPtr val_;
		std::string elem_type_;
	};

	class RenderVariableByteAddressBuffer : public RenderVariable
	{
	public:
		RenderVariablePtr Clone()
		{
			RenderVariablePtr ret = MakeSharedPtr<RenderVariableByteAddressBuffer>();
			GraphicsBufferPtr val;
			this->Value(val);
			*ret = val;
			std::string elem_type;
			this->Value(elem_type);
			*ret = elem_type;
			return ret;
		}

		RenderVariable& operator=(GraphicsBufferPtr const & value)
		{
			val_ = value;
			return *this;
		}

		void Value(GraphicsBufferPtr& val) const
		{
			val = val_;
		}

		RenderVariable& operator=(std::string const & value)
		{
			elem_type_ = value;
			return *this;
		}

		void Value(std::string& val) const
		{
			val = elem_type_;
		}

	protected:
		GraphicsBufferPtr val_;
		std::string elem_type_;
	};

	typedef RenderVariableConcrete<bool> RenderVariableBool;
	typedef RenderVariableConcrete<uint32_t> RenderVariableUInt;
	typedef RenderVariableConcrete<int32_t> RenderVariableInt;
	typedef RenderVariableConcrete<float> RenderVariableFloat;
	typedef RenderVariableConcrete<uint2> RenderVariableUInt2;
	typedef RenderVariableConcrete<uint3> RenderVariableUInt3;
	typedef RenderVariableConcrete<uint4> RenderVariableUInt4;
	typedef RenderVariableConcrete<int2> RenderVariableInt2;
	typedef RenderVariableConcrete<int3> RenderVariableInt3;
	typedef RenderVariableConcrete<int4> RenderVariableInt4;
	typedef RenderVariableConcrete<float2> RenderVariableFloat2;
	typedef RenderVariableConcrete<float3> RenderVariableFloat3;
	typedef RenderVariableConcrete<float4> RenderVariableFloat4;
	typedef RenderVariableConcrete<float4x4> RenderVariableFloat4x4;
	typedef RenderVariableConcrete<SamplerStateObjectPtr> RenderVariableSampler;
	typedef RenderVariableConcrete<std::string> RenderVariableString;
	typedef RenderVariableConcrete<shader_desc> RenderVariableShader;
	typedef RenderVariableConcrete<std::vector<bool> > RenderVariableBoolArray;
	typedef RenderVariableConcrete<std::vector<uint32_t> > RenderVariableUIntArray;
	typedef RenderVariableConcrete<std::vector<int32_t> > RenderVariableIntArray;
	typedef RenderVariableConcrete<std::vector<float> >  RenderVariableFloatArray;
	typedef RenderVariableConcrete<std::vector<int2> >  RenderVariableInt2Array;
	typedef RenderVariableConcrete<std::vector<int3> >  RenderVariableInt3Array;
	typedef RenderVariableConcrete<std::vector<int4> >  RenderVariableInt4Array;
	typedef RenderVariableConcrete<std::vector<float2> >  RenderVariableFloat2Array;
	typedef RenderVariableConcrete<std::vector<float3> >  RenderVariableFloat3Array;
	typedef RenderVariableConcrete<std::vector<float4> >  RenderVariableFloat4Array;
	typedef RenderVariableConcrete<std::vector<float4x4> >  RenderVariableFloat4x4Array;


	class KLAYGE_CORE_API RenderEffectAnnotation
	{
	public:
		void Load(XMLNodePtr const & node);

		void StreamIn(ResIdentifierPtr const & res);
		void StreamOut(std::ostream& os);

		uint32_t Type() const
		{
			return type_;
		}
		std::string const & Name() const
		{
			return name_;
		}

		template <typename T>
		void Value(T& val) const
		{
			var_->Value(val);
		}

	private:
		uint32_t type_;
		std::string name_;

		boost::shared_ptr<RenderVariable> var_;
	};

	class KLAYGE_CORE_API RenderShaderFunc
	{
	public:
		void Load(XMLNodePtr const & node);

		void StreamIn(ResIdentifierPtr const & res);
		void StreamOut(std::ostream& os);

		ShaderObject::ShaderType Type() const
		{
			return type_;
		}

		uint32_t Version() const
		{
			return version_;
		}

		std::string const & str() const
		{
			return str_;
		}

	private:
		ShaderObject::ShaderType type_;
		uint32_t version_;
		std::string str_;
	};

	// 渲染效果
	//////////////////////////////////////////////////////////////////////////////////
	class KLAYGE_CORE_API RenderEffect
	{
	public:
		RenderEffect();

		void Load(ResIdentifierPtr const & source, std::pair<std::string, std::string>* macros);

		bool StreamIn(ResIdentifierPtr const & source, std::pair<std::string, std::string>* predefined_macros,
			std::vector<std::vector<std::vector<uint8_t> > >& native_shader_blocks);
		void StreamOut(std::ostream& os, std::vector<std::vector<std::vector<uint8_t> > > const & native_shader_blocks);

		RenderEffectPtr Clone();

		std::string const & ResName() const
		{
			return *res_name_;
		}
		uint64_t Timestamp() const
		{
			return timestamp_;
		}
		uint64_t PredefinedMacrosHash() const
		{
			return predefined_macros_hash_;
		}

		void PrototypeEffect(RenderEffectPtr const & prototype_effect)
		{
			prototype_effect_ = prototype_effect;
		}
		RenderEffectPtr const & PrototypeEffect() const
		{
			return prototype_effect_;
		}

		uint32_t NumParameters() const
		{
			return static_cast<uint32_t>(params_.size());
		}
		RenderEffectParameterPtr ParameterBySemantic(std::string const & semantic) const;
		RenderEffectParameterPtr ParameterByName(std::string const & name) const;
		RenderEffectParameterPtr ParameterByIndex(uint32_t n) const
		{
			BOOST_ASSERT(n < this->NumParameters());
			return params_[n];
		}

		std::vector<std::pair<std::string, std::vector<uint32_t> > > const & CBuffers() const
		{
			return *cbuffers_;
		}

		uint32_t NumTechniques() const
		{
			return static_cast<uint32_t>(techniques_.size());
		}
		RenderTechniquePtr const & TechniqueByName(std::string const & name) const;
		RenderTechniquePtr const & TechniqueByIndex(uint32_t n) const
		{
			BOOST_ASSERT(n < this->NumTechniques());
			return techniques_[n];
		}

		uint32_t NumShaders() const
		{
			return shaders_ ? static_cast<uint32_t>(shaders_->size()) : 0;
		}
		RenderShaderFunc const & ShaderByIndex(uint32_t n) const
		{
			BOOST_ASSERT(n < this->NumShaders());
			return (*shaders_)[n];
		}

		uint32_t AddShaderDesc(shader_desc const & sd);
		shader_desc& GetShaderDesc(uint32_t id);
		shader_desc const & GetShaderDesc(uint32_t id) const;

		uint32_t NumMacros() const
		{
			return macros_ ? static_cast<uint32_t>(macros_->size()) : 0;
		}
		std::pair<std::string, std::string> const & MacroByIndex(uint32_t n) const
		{
			BOOST_ASSERT(n < this->NumMacros());
			return (*macros_)[n].first;
		}

		std::string const & TypeName(uint32_t code) const;

	private:
		boost::shared_ptr<std::string> res_name_;
		uint64_t timestamp_;
		uint64_t predefined_macros_hash_;

		std::vector<RenderEffectParameterPtr> params_;
		boost::shared_ptr<std::vector<std::pair<std::string, std::vector<uint32_t> > > > cbuffers_;
		std::vector<RenderTechniquePtr> techniques_;

		boost::shared_ptr<std::vector<std::pair<std::pair<std::string, std::string>, bool> > > macros_;
		boost::shared_ptr<std::vector<RenderShaderFunc> > shaders_;

		RenderEffectPtr prototype_effect_;

		boost::shared_ptr<std::vector<shader_desc> > shader_descs_;
	};

	class KLAYGE_CORE_API RenderTechnique : boost::noncopyable
	{
	public:
		explicit RenderTechnique(RenderEffect& effect)
			: effect_(effect)
		{
		}

		void Load(XMLNodePtr const & node, uint32_t tech_index);

		bool StreamIn(ResIdentifierPtr const & res, uint32_t tech_index,
			std::vector<std::vector<std::vector<uint8_t> > >& native_shader_blocks);
		void StreamOut(std::ostream& os, uint32_t tech_index,
			std::vector<std::vector<std::vector<uint8_t> > > const & native_shader_blocks);

		RenderTechniquePtr Clone(RenderEffect& effect);

		std::string const & Name() const
		{
			return *name_;
		}

		RenderEffect& Effect() const
		{
			return effect_;
		}

		uint32_t NumAnnotations() const
		{
			return annotations_ ? static_cast<uint32_t>(annotations_->size()) : 0;
		}
		RenderEffectAnnotationPtr const & Annotation(uint32_t n) const
		{
			BOOST_ASSERT(n < this->NumAnnotations());
			return (*annotations_)[n];
		}

		uint32_t NumPasses() const
		{
			return static_cast<uint32_t>(passes_.size());
		}
		RenderPassPtr const & Pass(uint32_t n) const
		{
			BOOST_ASSERT(n < this->NumPasses());
			return passes_[n];
		}

		bool Validate() const
		{
			return is_validate_;
		}

		float Weight() const
		{
			return weight_;
		}

		bool Transparent() const
		{
			return transparent_;
		}

		bool HasDiscard() const
		{
			return has_discard_;
		}
		bool HasTessellation() const
		{
			return has_tessellation_;
		}

	private:
		RenderEffect& effect_;
		boost::shared_ptr<std::string> name_;

		std::vector<RenderPassPtr> passes_;
		boost::shared_ptr<std::vector<RenderEffectAnnotationPtr> > annotations_;

		float weight_;
		bool transparent_;

		bool is_validate_;
		bool has_discard_;
		bool has_tessellation_;
	};

	class KLAYGE_CORE_API RenderPass : boost::noncopyable
	{
	public:
		explicit RenderPass(RenderEffect& effect)
			: effect_(effect),
				front_stencil_ref_(0), back_stencil_ref_(0),
				blend_factor_(1, 1, 1, 1), sample_mask_(0xFFFFFFFF)
		{
		}

		void Load(XMLNodePtr const & node, uint32_t tech_index, uint32_t pass_index, RenderPassPtr const & inherit_pass);

		bool StreamIn(ResIdentifierPtr const & res, uint32_t tech_index, uint32_t pass_index,
			std::vector<std::vector<std::vector<uint8_t> > >& native_shader_blocks);
		void StreamOut(std::ostream& os, uint32_t tech_index, uint32_t pass_index,
			std::vector<std::vector<std::vector<uint8_t> > > const & native_shader_blocks);

		RenderPassPtr Clone(RenderEffect& effect);

		std::string const & Name() const
		{
			return *name_;
		}

		void Bind();
		void Unbind();

		bool Validate() const
		{
			return is_validate_;
		}

		RasterizerStateObjectPtr const & GetRasterizerStateObject() const
		{
			return rasterizer_state_obj_;
		}
		DepthStencilStateObjectPtr const & GetDepthStencilStateObject() const
		{
			return depth_stencil_state_obj_;
		}
		BlendStateObjectPtr const & GetBlendStateObject() const
		{
			return blend_state_obj_;
		}
		ShaderObjectPtr const & GetShaderObject() const
		{
			return shader_obj_;
		}

		uint32_t NumAnnotations() const
		{
			return annotations_ ? static_cast<uint32_t>(annotations_->size()) : 0;
		}
		RenderEffectAnnotationPtr const & Annotation(uint32_t n) const
		{
			BOOST_ASSERT(n < this->NumAnnotations());
			return (*annotations_)[n];
		}

	private:
		RenderEffect& effect_;

		boost::shared_ptr<std::string> name_;
		boost::shared_ptr<std::vector<RenderEffectAnnotationPtr> > annotations_;
		boost::shared_ptr<std::vector<uint32_t> > shader_desc_ids_;

		RasterizerStateObjectPtr rasterizer_state_obj_;
		DepthStencilStateObjectPtr depth_stencil_state_obj_;
		uint16_t front_stencil_ref_, back_stencil_ref_;
		BlendStateObjectPtr blend_state_obj_;
		Color blend_factor_;
		uint32_t sample_mask_;
		ShaderObjectPtr shader_obj_;

		bool is_validate_;
	};

	class KLAYGE_CORE_API RenderEffectParameter : boost::noncopyable
	{
	public:
		explicit RenderEffectParameter(RenderEffect& effect);
		~RenderEffectParameter();

		void Load(XMLNodePtr const & node);

		void StreamIn(ResIdentifierPtr const & res);
		void StreamOut(std::ostream& os);

		RenderEffectParameterPtr Clone(RenderEffect& effect);

		uint32_t type() const
		{
			return type_;
		}

		RenderVariablePtr const & var() const
		{
			return var_;
		}

		boost::shared_ptr<std::string> const & ArraySize() const
		{
			return array_size_;
		}

		boost::shared_ptr<std::string> const & Name() const
		{
			return name_;
		}
		boost::shared_ptr<std::string> const & Semantic() const
		{
			return semantic_;
		}

		uint32_t NumAnnotations() const
		{
			return annotations_ ? static_cast<uint32_t>(annotations_->size()) : 0;
		}
		RenderEffectAnnotationPtr const & Annotation(uint32_t n)
		{
			BOOST_ASSERT(n < this->NumAnnotations());
			return (*annotations_)[n];
		}

		template <typename T>
		RenderEffectParameter& operator=(T const & value)
		{
			*var_ = value;
			return *this;
		}

		template <typename T>
		void Value(T& val) const
		{
			var_->Value(val);
		}

	private:
		RenderEffect& effect_;

		boost::shared_ptr<std::string> name_;
		boost::shared_ptr<std::string> semantic_;

		uint32_t type_;
		boost::shared_ptr<RenderVariable> var_;
		boost::shared_ptr<std::string> array_size_;

		boost::shared_ptr<std::vector<RenderEffectAnnotationPtr> > annotations_;
	};
}

#endif		// _RENDEREFFECT_HPP
