class TestDocument < Test::Unit::TestCase
  sub_test_case("#initialize") do
    def test_data
      pdf = StringIO.new
      surface = Cairo::PDFSurface.new(pdf, 100, 100)
      context = Cairo::Context.new(surface)
      context.show_text("Hello")
      surface.finish

      document = Poppler::Document.new(:data => pdf.string)
      assert_equal("Hello", document[0].text)
    end
  end

  def test_save
    saved_pdf = File.join(tmp_dir, "saved.pdf")
    FileUtils.rm_f(saved_pdf)

    document = Poppler::Document.new(text_field_pdf)
    find_first_text_field(document).text = "XXX"
    document.save(saved_pdf)
    reread_document = Poppler::Document.new(saved_pdf)
    assert_equal("XXX", find_first_text_field(reread_document).text)
  end

  def test_save_a_copy
    copied_pdf = File.join(tmp_dir, "copied.pdf")
    FileUtils.rm_f(copied_pdf)

    document = Poppler::Document.new(text_field_pdf)
    first_text_field = find_first_text_field(document)
    default_text = first_text_field.text
    first_text_field.text = "XXX"
    document.save_a_copy(copied_pdf)
    reread_document = Poppler::Document.new(copied_pdf)
    assert_equal(default_text, find_first_text_field(reread_document).text)
  end

  def test_each
    document = Poppler::Document.new(multiple_pages_pdf)
    texts = []
    document.each do |page|
      texts << page.text
    end
    assert_equal(["The first page", "The second page"],
                 texts)
  end

  def test_each_enumerator
    document = Poppler::Document.new(multiple_pages_pdf)
    assert_equal(["The first page", "The second page"],
                 document.each.collect(&:text))
  end

  def test_enumerable
    document = Poppler::Document.new(multiple_pages_pdf)
    assert_equal(["The first page", "The second page"],
                 document.collect(&:text))
  end

  def test_size
    document = Poppler::Document.new(multiple_pages_pdf)
    assert_equal(2, document.size)
  end

  def test_pages
    document = Poppler::Document.new(multiple_pages_pdf)
    assert_equal(["The first page", "The second page"],
                 document.pages.collect(&:text))
  end

  private
  def find_first_text_field(document)
    document.each do |page|
      page.form_field_mapping.each do |mapping|
        field = mapping.field
        return field if field.is_a?(Poppler::TextField)
      end
    end
  end
end
